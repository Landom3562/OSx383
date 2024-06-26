# OSx383
Term project for the cource CENG383 real time systems at IZTECH

Functions of the Operating system:

# Clock

* After booting up, OS displays clock on the screen. Below are the requirements for the clock:

* Current time is read from CMOS RTC

* Clock stays on the top right corner of the screen no matter what

* Clock updates are seamless.

* Clock updates are performed using the timer interrupt.

* Clock is in 24-hour format

* Single digit hour, minute, second values are zero padded

# Command Shell

* Operating system provides users a shell that can run commands. Shell meets the specifications below:

* "help", "settime" and "reboot" commands are supported

* If an invalid command is entered, the user is encouraged to use help

* help command provides the user a list of available commands

* settime command updates the CMOS RTC with the value entered (clock continues from the new time)

* If any command is called with invalid parameters, the user will be presented with the correct usage

* reboot command will return the OS to its initial state

# Colors

* Welcome message: light green over black

* Clock face: yellow over dark gray

* Command prompt: cyan over black

* Anything else: white over black

# Task Mechanism:

There are tasks that can be scheduled in the operating system. Tasks can be periodic and aperiodic. Tasks that are periodic is run at each period and aperiodic tasks are run once.
Periodic tasks has a timer that make them be able to run at their periods. All tasks also has a priority so if there are two tasks waiting at the ready queue, first the higher priority one is run.

# Time Management:

This os has a time management system that is related to the timer interrupt(IRQ0) of the cpu. The timer fires at each milisecond.

# Scheduler:

Scheduler is preemtive and priority based. The scheduler runs in a round-robin fashion. The fixed quantum time is 10ms.

