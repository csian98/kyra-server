/**
 * @file		main.cpp
 * @author		Jeong Hoon (Sian) Choi
 */

/* Copyright (C)
 * 2026 - Jeong Hoon (Sian) Choi
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 */

#include <iostream>

#include "kyra-server.h"

#define OS_WINDOWS	0
#define OS_LINUX	1

#ifdef _WIN32
#define _TARGET_OS	OS_WINDOWS
#else
	#define _TARGET_OS	OS_LINUX
#endif

#if _TARGET_OS == OS_WINDOWS

#elif _TARGET_OS == OS_LINUX

//void custom_terminate_fnct(void) {
//	exit(1);
//}

int main(int argc, char* argv[]) {
// 	std::terminate_handler default_terminate =
//	std::set_terminate(&custom_terminate_fnct);

	try {
		kyra::DatabaseConfig config;
		config.host = "127.0.0.1";
		config.port = 3306;
		config.user = "kyra";
		config.password = "kyra";
		config.database = "kyra";
		config.pool_size = 4;

		// cron timezone resolver
		auto cron_db = std::make_shared<kyra::DatabaseHandle>(config);
		auto& cron = kyra::CronHandle::get_instance();
		cron.set_timezone_resolver(
			[cron_db](const std::string& username) -> std::optional<std::string> {
				auto user = cron_db->find_user_by_username(username);
				if (!user)
					return std::nullopt;
				auto profile = cron_db->find_profile_by_uid(user->id);
				if (!profile || profile->time_zone.empty())
					return std::nullopt;
				return profile->time_zone;
			});

		// initialize
		kyra::MemoryServer::get_instance().start();
		kyra::FrameServer::get_instance().start();
		kyra::CronHandle::get_instance().initialize("etc/cron/crontab");
		kyra::CronHandle::get_instance().start();
		kyra::SessionHub::get_instance().initialize(config);
		kyra::Service::get_instance();
		
        kyra::Server server;
        server.run();

		kyra::CronHandle::get_instance().stop();
		kyra::MemoryServer::get_instance().stop();
    } catch (std::exception& e) {
        std::cerr << e.what() << "\n";
		kyra::CronHandle::get_instance().stop();
		kyra::MemoryServer::get_instance().stop();
		return 1;
    }

	return 0;
}

#endif // OS dependency
