# ESP-IDF on Visual Studio Code
## Prerequisites
### Visual Studio Code
In order to work with ESP-IDF, you will need to have a working Visual Studio Code install. Refer to the following link if it is not already the case : https://code.visualstudio.com/download

A working Python3 install is also required, as well as Pip. Refer to the following links to install Python and Pip on Windows:<br>
- Download page: https://www.python.org/downloads/<br>
- Installation guide: https://docs.python.org/3/using/windows.html

On Linux, Python3 comes pre-installed on most distros. Otherwise, refer to your distro's reference to install it. If your distro uses it, the `apt` package manager can be used to install Pip if it is missing:
```
sudo apt install python3-pip
```
### Clean system
You should only work through Vscode's ESP-IDF extension. Make sure that any previous ESP-IDF installs are removed to avoid conflicts. Do __not__ install ESP-IDF from the website manually, as this is far from being a foolproof process.

## Installing and using ESP-IDF

Follow the guides on the following link, starting with `install.md` : https://github.com/espressif/vscode-esp-idf-extension/blob/HEAD/docs/tutorial

Here you will find the ESP-IDF extension guides, including how to create template projects, use debugging functionalities, or how to configure your system if you are using WSL.

__It is strongly recommended that you check `basic_use.md` before getting started.__

You can also refer to the extension's page within Vscode to find useful links, functionalities wrap-up, and shortcuts descriptions.
