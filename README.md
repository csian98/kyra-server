<!-- 
	***
	*   README.md
	*	
	*	Author: Jeong Hoon (Sian) Choi
	*	License: MIT
	*	
	***
-->
<a name="readme-top"></a>

<br/>
<div align="center">
	<a href="https://github.com/csian98/sian">
		<img src="images/logo.png" alt="Logo" width="150" height="150">
	</a>
	<h3 align="center">Kyra-Server</h3>
	<a href="mailto:csian7386@gmail.com"><img src="https://img.shields.io/badge/csian7386@gmail.com-grey?logo=Gmail"></a>
	<a href="https://instagram/csian98"><img src="https://img.shields.io/badge/csian98-grey?logo=Instagram"></a>
	<a href="https://discord.gg/YhghyDBgKa"><img src="https://img.shields.io/badge/Discord-grey?logo=Discord"></a>
	<a href="https://csian98.github.io"><img src="https://img.shields.io/badge/csian98.github.io-grey?logo=Homepage"></a>
	<a href="https://www.linkedin.com/in/csian98"><img src="https://img.shields.io/badge/LinkedIn-grey?logo=linkedin"></a>
	<a href="https://patreon.com/csian98"><img src="https://img.shields.io/badge/Patreon-grey?logo=Patreon"></a>
	<p align="center">
	<br/>
	<br/>
	<a href="https://github.com/csian98/sian">
		<strong>Explore the docs »</strong>
	</a>
	<br/>
	<br/>
	<a href="https://github.com/csian98/kyra-server/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
	·
	<a href="https://github.com/csian98/kyra-server/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
	</p>
</div>

## About The Project

![Language][language-shield]
![repo size][repo-size-shield]
![weekly commits][commit-activity-shield]
![last commit][last-commit-shield]
[![MIT License][license-shield]][license-url]

![Kyra Server Screen Shot](images/screenshot.png)

Kyra is a C/C++ based Local AI Agent system developed by Jeong Hoon Choi for personal use.

Kyra is designed to operate entirely on a self-hosted environment, allowing local LLM inference, speech processing, and extensible tool usage through the Model Context Protocol (MCP).

The system communicaties with clients through WebSocket Secure (WSS) and uses Bearer Token authentication for secure access.

Kyra supports multiple input and output modalities:

Input:
* TEXT
* AUDIO (STT)
* IMAGE (Optional)

Output:
* TEXT
* AUDIO (TTS)

### Default AI Stack

Kyra is designed to run using fully local AI components by default.

| Component | Purpose                 |
|-----------|-------------------------|
| Ollama    | Local LLM Inference     |
| Whisper   | Speech-To-Text          |
| Piper     | Text-To-Speech          |
| Qdrant    | Long-Term vector memory |

### Required Services

The following services must be running for Kyra to operate correctly.

#### Ollama (LLM)

Default endpoint:

``` text
http://localhost:11434
```

Ollama runs a local HTTP server which Kyra uses for LLM inference.
Internally, a total of three models are used by default.

| Model    | Purpose                                                   |
|----------|-----------------------------------------------------------|
| kyra     | Model for basic generate, chat, and tool using            |
| kyra-vl  | Model including OCR and image processing capabilities     |
| kyra-emb | Small model for compression to manage coversation context |

#### Qdrant (Vector Database)

Default endpoint:

``` text
http://localhost:6333
```

### MCP Servers

Kyra integrates with multiple MCP servers to extend the capabilities of the LLM.

The following servers are included by default:
| MCP Server                          | Purpose              |
|-------------------------------------|----------------------|
| time                                | time utilities       |
| mem0 + Qdrant (customize for local) | long-term memory     |
| memory (knowledge-graph)            | long-term memory     |
| Brave Search                        | web search           |
| CalDAV                              | calendar integration |

Configuration is defined in:

```
etc/mcp-server/config.json
```

### Kyra-Clients
Currently implemented clients:


#### Kyra-Client for Emacs
<img src="images/kyra-client-emacs.png">

#### Kyra-Client for Qt App (implement for mac)
<img src="images/kyra-client-app.png">

#### Kyra-Client for Raspberry Pi
Voice-only interface for physical interaction.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Development Environment
* [![macOS][macos-shield]][macos-url]
* [![Arch Linux][archlinux-shield]][archlinux-url]
* [![cpp][cpp-shield]][cpp-url]
* [![python][python-shield]][python-url]
* [![Nvidia Cuda][cuda-shield]][cuda-url]

### Built With
* [![ollama][ollama-shield]][ollama-url]
* [![huggingface][hugging-face-shield]][huggingface-url]
* [![qt][qt-shield]][qt-url]
* [![blender][blender-shield]][blender-url]

## 🔐 License

Copyright © 2026, *Jeong Hoon Choi* or *Sian*. All rights reserved
Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## 📞 Contact

Jeong Hoon (Sian) Choi - [@csian98](https://instagram.com/csian98) - [csian7386@gmail.com](mailto:csian7386@gmail.com)

Project Link: [https://github.com/csian98/sian](https://github.com/csian98/kyra-server)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[language-shield]: https://img.shields.io/github/languages/top/csian98/kyra-server.svg?style=for-the-badge
[code-size-shield]: https://img.shields.io/github/languages/code-size/csian98/kyra-server.svg?style=for-the-badge
[repo-size-shield]: https://img.shields.io/github/repo-size/csian98/kyra-server.svg?style=for-the-badge
[commit-activity-shield]: https://img.shields.io/github/commit-activity/w/csian98/kyra-server.svg?style=for-the-badge
[last-commit-shield]: https://img.shields.io/github/last-commit/csian98/kyra-server.svg?style=for-the-badge
[license-shield]: https://img.shields.io/github/license/csian98/kyra-server.svg?style=for-the-badge
[license-url]: https://github.com/csian98/kyra-server/blob/main/LICENSE

[macos-shield]: https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=macos&logoColor=F0F0F0
[macos-url]: https://developer.apple.com/macos
[archlinux-shield]: https://img.shields.io/badge/Arch%20Linux-1793D1?logo=arch-linux&logoColor=fff&style=for-the-badge
[archlinux-url]: https://archlinux.org
[cuda-shield]: https://img.shields.io/badge/NVIDIA%20CUDA-RTX4060-76B900?style=for-the-badge&logo=nvidia&logoColor=white
[cuda-url]: https://docs.nvidia.com/cuda/cuda-c-programming-guide/

[openssl-shield]: https://img.shields.io/badge/OpenSSL-721412?style=for-the-badge&logo=OpenSSL
[openssl-url]: https://www.openssl.org
[curl-shield]: https://img.shields.io/badge/curl-073551?style=for-the-badge&logo=curl
[curl-url]: https://curl.se
[ollama-shield]: https://img.shields.io/badge/ollama-%23000000.svg?style=for-the-badge&logo=ollama&logoColor=white
[ollama-url]:https://ollama.com
[huggingface-shield]: https://img.shields.io/badge/huggingface-%23FFD21E.svg?style=for-the-badge&logo=huggingface&logoColor=white
[huggingface-url]:https://huggingface.co
[qt-shield]: https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white
[qt-url]: https://www.qt.io/development/qt-framework/qt6
[emacs-shield]: https://img.shields.io/badge/Emacs-%237F5AB6.svg?&style=for-the-badge&logo=gnu-emacs&logoColor=white
[emacs-url]: https://www.gnu.org/software/emacs/
[blender-shield]: https://img.shields.io/badge/blender-%23F5792A.svg?style=for-the-badge&logo=blender&logoColor=white
[blender-url]: https://www.blender.org

[c-shield]: https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white
[cpp-shield]: https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white
[python-shield]: https://img.shields.io/badge/Python-FFD43B?style=for-the-badge&logo=python&logoColor=blue
[elisp-shield]: https://img.shields.io/badge/Emacs%20Lisp-%237F5AB6.svg?&style=for-the-badge&logo=gnu-emacs&logoColor=white
[r-shield]: https://img.shields.io/badge/R-276DC3?style=for-the-badge&logo=r&logoColor=white
[shell-shield]: https://img.shields.io/badge/Shell_Script-121011?style=for-the-badge&logo=gnu-bash&logoColor=white
