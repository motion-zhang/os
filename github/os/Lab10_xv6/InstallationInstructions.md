# Introduction

This file contains information for installing and running xv6. Please read this for your respective operating system if you were not able to previously obtain xv6 and get it running in the QEMU emulator.

## Task 1 - Install an emulator and Build xv6

For this lab we need to install an emulator that can emulate an operating system. Because we do not want to dedicate our personal machines to installing xv6 (although we could!). You will do this locally on your machine.

1. The first step is to install QEMU by navigating to https://www.qemu.org/download/#linux. You may follow the directions here, or I have highlighted them below for several platforms.

### Linux

- Run the following on the terminal: `sudo apt-get install qemu`

See: https://www.qemu.org/download/#linux for the official instructions.

### Windows 7 or earlier.

(If you have Windows 10, you can skip these steps and navigate below to 'Install xv6')

- Download the appropriate binary from: https://www.qemu.org/download/#windows
  - The exact download I used for my Windows x86_64 machine was: https://qemu.weilnetz.de/w64/2018/qemu-w64-setup-20180711.exe
  - Run the installer with the default settings.
  - You can launch the executable to test it out (e.g. from C:\Program Files\qemu\qemu-system-x86_64w.exe)
    - However, we do not have xv6 installed quite yet! Keep reading.
    
See: https://www.qemu.org/download/#windows for the official instructions.

### Mac

- You will need either 'brew' or 'ports' to install QEMU
  - I recommend installing brew which can be done here: https://brew.sh/
  - Close and then open your terminal after installing.
  - Then follow the commands on page 86 of https://docs.google.com/presentation/d/1qzv18SILfoXUz9xnXTiJiMb56XXkxrORYxLRIHPtsw8/edit?usp=sharing

See: https://pdos.csail.mit.edu/6.828/2018/tools.html for the official instructions.

### Building from source

If none of the above options work, you can try to build from source for your architecture. This is a good skill to have, but may take some time and additional configuring. See (https://www.qemu.org/download/#source) for directions.

## Task 2 - Install xv6

(The official instructions are here: https://pdos.csail.mit.edu/6.828/2017/xv6.html)

We are going to run xv6 in an emulator--specifically the QEMU emulator that you built above. What this means is we now need to compile the xv6 operating system into a format that our emulator understands. If you are using linux, this is relatively straight forward. If you are not using Linux, then we need to 'cross-compile' the binary.

Cross-compiling means to generate a binary file that is not necessarily for our native platform. That is, if you are windows normally when you compile, executables are generaetd that run on windows. So what is different if we are on windows, is we want to generate a binary that actually is of the ELF format (which windows does not understand, but our emulator will).

Proceed to the directions below.

### Obtaining xv6

xv6 lives in a github repository for the MIT operating systems class. 

- Obtain the repository here: `git clone git://github.com/mit-pdos/xv6-public.git`

### Building xv6 on Linux

1. Once the repository has downloaded run navigate inside the `public-xv6` folder.
2. Type `make` within the public-xv6 repository you have downloaded and wait a few seconds for the OS to compile. 

### Building xv6 on Mac

- I recommend following the instructions at https://pdos.csail.mit.edu/6.828/2018/xv6.html
- There is a summary on page 86 of https://docs.google.com/presentation/d/1qzv18SILfoXUz9xnXTiJiMb56XXkxrORYxLRIHPtsw8/edit?usp=sharing
- Otherwise the general steps are below.

1. Install gcc/Xcode. (Clang will not work)
2. Add some needed packages using brew
3. Once the repository has downloaded run navigate inside the `public-xv6` folder.
4. Update makefile with the location of the qemu binary 
5. Within the xv6 dirctory you have cloned, type: 'make TOOLPREFIX=i386-elf-'
6. Install any missing tools needed, and retry the make command.

### Building xv6 on Windows

If you have Windows 10 64-bit follow the directions below.

- Follow the instructions here: https://gcallah.github.io/OperatingSystems/xv6Install.html (I have also written them below)

1. From within Bash on on windows(https://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/) type the following: `sudo apt-get update && sudo apt-get install git nasm build-essential qemu gdb`
2. Then within the MakeFile in the directory modify `QEMUOPTS = -hdb fs.img xv6.img -smp $(CPUS) -m 512 $(QEMUEXTRA)` **to** `QEMUOPTS = -hdb fs.img xv6.img -smp $(CPUS) -m 512 $(QEMUEXTRA) -display none`

If you have Windows 7 or earlier, you will need to install cygwin or some other terminal, and follow similar instructions to the Mac.

## After building xv6 -- Actually running xv6

Okay great, what did we achieve? After building xv6 you should see the `fs.img and xv6.img` This is an 'image' of your operating system. In other words, you whole operating system wrapped up into a single file. The emulator (qemu) will then boot up the operating system from within this image file, and host it in a virtualized environment.

Okay, final step from whatever terminal you are working in.

- If you are working in Unix, or on Mac, it should be as simple as typeing `make qemu-nox` and the operating system will begin in your current shell! (If for some reason that does not work, you can try `make qemu`)
- If you are running in the Windows Linux subsystem run: `make qemu fs.img`
