To run any of the three versions of this program first run the make file through calling "make".

Version #1 (Part B):
To run version 1 after calling make file call "./observer" with no other arguments. Once called
you will be presented with the Cpu model name, Linux kernel version, uptime, and date.

Version #2 (Part C):
To run version 2 you would call "./observer" like in version 1 but afer observer you would add a
" -s" to let the program know to run the short version of this program. Included in this version
is everything inside of version 1 along with time Cpu  spent in three modes(user, system, and 
idle mode), number of read/write requests, number of context switches, and number of processes 
created.

Version #3 (Part D):
To run this version you would call "./observer" followed by an " -l [interval] [duration]" where
interval and duration will be replaced with integers to determine how often and how long to load 
averages. Included in this version is everything inside of version 2 along with the amount of 
memory configured, Memory available, and a list of load averages for as long as you specify.
