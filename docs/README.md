# WSL and VSCode

I want to share a couple of time-saving tools with other students at UWB for CSS courses that require deployment on linux or a remote machine (like CSS342, CSS343, CSS430... etc.).



I'm recommending a code-editor that makes development on a remote environment (like the Linux Labs) easy. I'm also recommending an alternative to the Linux Lab if you don't have access to it or if you develop your code on your personal computer. You can use both at the same time.



## Visual Studio Code

You can use Visual [Studio Code (**VSCode**)](https://code.visualstudio.com/) to edit, compile, and run your code. VSCode is a text-editor that works on Windows, Linux, and Mac.



VSCode is modularized so you can use it for almost everything. To write C/C++, you would have to install the C/C++ extension inside VSCode. You can also use VSCode for Java if you install JDK and the Java extension of VSCode.



I recommend VSCode because it allows [remote development](https://code.visualstudio.com/docs/remote/ssh). You can edit code on a remote machine (Like UWB's Linux lab) and it will feel like you are editing files on you personal computer. VSCode is saves a lot of time. You can use the remote development for Windows Subsystem for Linux too.



## Windows Subsystem for Linux

Windows Subsystem for Linux (**WSL**) allows developers to run a Linux environment on their windows machine ([more info](https://docs.microsoft.com/en-us/windows/wsl/about)). 



So, you can compile and execute your C++ code on your personal computer using WSL instead of relying on the UWB Linux lab. 



[To get WSL for Windows 10.](https://docs.microsoft.com/en-us/windows/wsl/install-win10) I recommend WSL-2.

[A comparison between WSL-1 and WSL-2](https://docs.microsoft.com/en-us/windows/wsl/compare-versions)



I wrote a simple program that tests the basic needs of CSS courses at UWB so you can test your WSL environment.



## Thoughts

You can use VSCode without WSL. For example, you can setup a remote environment on UWB's Linux labs.



Similarly, You can use WSL without VSCode. You can edit your code using your favorite editor and just test it with WSL before you submit it. For example, you can use [Visual Studio IDE](https://visualstudio.microsoft.com/) (not the same as VSCode) while developing and for your final tests, you can then compile and run your code with WSL.



I just wanted to share these fancy tools which save a lot of time.







