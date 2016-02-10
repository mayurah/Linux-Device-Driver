# Linux Device Driver

> A kickstart manual and a practical approach to learn internals of how Linux Kernel and Device Driver works.

**Update [2016]:** This is also a base repository, which should be cloned and used by participants of HP-E Mastermaze.

## What can you learn from this

- **Create** a Linux kernel driver which allocates a **4k byte** memory page and **shares** it with **user-process** which requests **read access**. 
- The driver is expected to **listen** to on **/dev/hpehackon**. The driver should return the address of the 4k byte memory when user process does a **mmap()** on the **fd associated** with /dev/hpehackon.
- When the **userprocess** reads the **first 256 bytes** as a string from the return address, it should contain “HPE HACKATHON 2016!!” within it.

## Tech Stack

- Linux
- Device Drivers written in code C
- File Operations and Memory allocation via mmap.


**[Guideline]**

* **Platform:** Linux
* Note: The driver should be developed by you and the executable userprocess given in this repository should able to communicate with driver listening on /dev/hpehackon.
* Install Git and Clone this repo via 

```
# sudo apt-get install git
# sudo su
# git clone git@github.com:mayurah/Linux-Device-Driver.git
```

* do a chmod on user process 

```
# chmod +x uprog_validate
# ./uprog_validate
```


**[References]**

* http://www.linuxdevcenter.com/pub/a/linux/2007/07/05/devhelloworld-a-simple-introduction-to-device-drivers-under-linux.html
* https://en.wikipedia.org/wiki/Mmap

