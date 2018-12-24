### TODO Please edit the following information in your assignment

- Name(s): Liangmou Zhang
- How many hours did it take you to complete this lab? 7
- Did you collaborate with any other students/TAs/Professors? No
- Did you use any external resources? (Cite them below)
  - https://www.youtube.com/watch?v=3eODpQQAmTE

- (Optional) What was your favorite part of the assignment?
- (Optional) How would you improve the assignment?

# Logistics

For this assignment (and every assignment/lab), you must login into the servers through `your_ccis_name@login.ccs.neu.edu` to complete and test your work. The reason is the examples I will provide below are compiled strictly for our machines architecture, and this is a consistent architecture where your submission will be graded.

# Automate (some of) your life

Getting familiar with the terminal is a fundamental skill to have. Many of you have various levels of experience using the terminal.

For this assignment, you will be warming up by writing a 1-2 page tutorial on bash scripting. Your tutorial will be embededded in a shell script, explaining how to do something on the terminal that is non-trivial but that can be automated. You will run your script by typing `sh myScript.sh` on the command line as an executable shell script(sh is the GNU Bourne-Again SHell -- type 'man sh' for more information).  You can look at example 'sh' scripts for inspiration on what you can achieve on the web and cite them appropriately. 

The tutorial will be done purely in text and and within a file called 'myscript.sh'. You are required to type your tutorial using a terminal based text editor like 'vim', 'emacs', or 'nano' to write your tutorial (I personally use the vim text editor).

Examples of a non-trivial scripts

* Sort a particular column of data from a .csv file (e.g. stock prices). Then print out the top ten values, and the average of that column of data.
* Write a shell script that allows you to query information about your computer system from a menu of options. Users might like to know information like hard drive space, if a graphics card is available, how fast the cpu is, etc.
* Write a shell script that downloads a webpage (using wget, perhaps to grab some json data), then parses some of the data, and prints it to the terminal. 
* You can use your imagination to create other examples.

# Part 1 - myScript.sh

<img align="right" width="300px" src="https://cdn-images-1.medium.com/max/1600/1*MaSfT-bQOxfWnKjFPxMg6g.gif">

## Very Brief Example Tutorial (Template)
(Note this example is fairly trivial, probably worth a C-. You can use it as a template)

```
# Problem Statement: "Often I have to search for different files and directories within my computer system. 
#                     In order to do this I use the 'ls' command to help orient myself.
# Name of command: ls
# Example of its usage: 
# -bash-4.2$ ls
# Lab1  README.md

# Here is the myScript.sh script that can list the directories and how many total directories are in the current folder.
# usage: sh myScript.sh

ls
ls | wc -l
```

# Part 2 - VIM and TMUX

<img align="right" width="300px" src="https://joshldavis.com/img/vim/tabs.gif">

(Note this part is ungraded--but you are required to do it!)

Figuring out a good workflow on Unix, Mac, (and even windows) is an important part of becoming a good programmer. My work environment (and the suggested one so I can help you during class), is to use the combination of the VIM text editor and tmux window manager to program your assignments in.

### Student and Teacher Dialouge

*"But I love visual studio, sublime, XCode, Atom, etc."*

*That's great, but you cannot use those in a remote environment easily--so I suggest learning another skill. By all means, use both or multiple tools to write the highest quality code.*

*"Hehe, the professor will never know if I just use notepad. I'll just take a shortcut on this assignment"*

*While that's true you can take a shortcut now, it will eventually catch up to you. I promise this is a good skill to learn! This first assignment is much more lightweight, take the time now to do things properly.*

Here are some suggested resources to get started.
* (VIM+TMUX Example) https://www.youtube.com/watch?v=YD9aFIvlQYs (16:31)
* Type *man tmux* in a terminal.
* Tmux tutorial - https://www.youtube.com/watch?v=BHhA_ZKjyxo (11:23)

# Part 3 - The Network is down! How to work locally.

Sometimes ssh is not available if the internet is not. Hmm, how will we then work on our CCIS machines which are in a linux environment? The solution is to install locally (i.e. your desktop machine) a virtual machine. A virtual machine emulates an entire operating system!

The instructions to get setup are here:

**Note** If you are on windows and have the Windows Linux Subsystem, you can submit a screenshot of that running. That *should be* sufficient for most things in this course. And if you are using linux...just submit a screenshot of your desktop (You may still find the exercise useful however--especially if you want to test software on multiple OS's).

* First start downloading the operating system I recommend using: Ubuntu https://www.ubuntu.com/download/desktop
  * While our CCIS machines are actually CentOS for the operating system, Ubuntu will work just fine (They core kernel is the same).
  * The download is rather large, so start with this step! :)
* Visit https://www.virtualbox.org/
* Download the binary for Virtual box 5.2 or later.
  1. This will show up as "Windows hosts" for window users, OSX hosts for mac users, etc.
* Install the program using the default installation settings (i.e. you will click 'next' a bunch of times).
* When installation has completed, launch Virtaul Box.
* Next click 'new' in the top right, and select *Linux* from the 'Type' dropbown box.
  1. You can name it something like 'myUbuntuMachine'
  2. Click 'next'
  3. You can then configure the memory size. I recommend at least 4096 MB (Unless that is not more than half of what you have available).
  4. Click 'next' and then create a Virtual Hard disk(default option). This essentially creates a giant file that acts like a hard drive.
  5. You can create a VDI (Virtual Disk Image). Click next.
  6. For the storage, you can select 'Dynamically allocated'
* Okay, now you are configured, and ready to boot your OS!
  1. Go ahead and right-click on your machine name, and select 'start'. 
  2. This will begin launching your virtual machine (It may take a few minutes to create some files)
  3. The first dialog will ask where your media is, and you will select wherever you downloaded the Ubuntu 18 .iso file (in step 1).
  4. Then run through the 'normal install'
  5. Follow the dialogs to install Ubuntu.
  6. Remember, you are working within a virtual environment, so this installation is only taking place within virtual box.
  7. From within Ubuntu, try opening a terminal. Run `sudo apt-get install build-essential` to make sure you get some tools(like our compiler gcc) setup.

Again, if you have a linux machine you may not need a virtual machine. What is nice about a virtual machine however, is if you mess something up, you can always reboot it and start from scratch very easily.

# Resources to help

- A pretty good introduction to shell scripting is here: https://www.howtogeek.com/67469/the-beginners-guide-to-shell-scripting-the-basics/ .

# Rubric

* 30% Was your tutorial 1-2 pages (estimate this as 2 regular pieces of printed paper)
    * (If you decided you were doing something so cool it had to be longer, was this well justifed)
    * If your tutorial is your actual script with comments in it, then it should be able to run. Otherwise, you should also have a script file that can actually be run accompanying your tutorial.
* 30% Polish
    * Was the tutorial well polished, did something useful, and did not contain any bugs?
* 30% Presentation
    * Was the writing presented in a clear manner in your own voice (i.e. I should not be able to Google it).
  * (Please indicate in your submission at the top if these tutorials can be shared on our piazza board)
  * (The very brief tutorial example I gave would probably earn a C- at best :) Go beyond!)
* 10% Take a screenshot of your virtual environment running. Name it 'linux.jpg'
  * Make sure to 'commit' this file to the repo in this directory.

* Note: Your code **must** run on the CCIS machines. That is where you should test it, and this is where we grade it!
* Note: You must also commit any additional files into your repository so we can test your code.
  * Points will be lost if you forget!

# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

Read this article and implement the little 'whatis' command in your .bashrc. https://lifehacker.com/how-can-i-quickly-learn-terminal-commands-1494082178

```
echo "Did you know that:"; whatis $(ls /bin | shuf -n 1)
```

This is a nice way to learn a new command everytime you log on!

