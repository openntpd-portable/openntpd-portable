This is the portable version of OpenBSD's native Network Time Protocol daemon,
OpenNTPD http://www.openntpd.org/

## Platform Requirements

 - adjtime(2) and settimeofday(2) syscalls or equivalent.
 - adjfreq(2) or an equivalent compatibility function for best results
 - daemon(3), setresgid(2), setresuid(2) or equivalent
 - a working arc4random(2) implementation (this project shares the same
   arc4random compatibility code from LibreSSL)
 - libtls from LibreSSL 3.0+ is required for HTTPS time constraint validation.

## Supported Operating Systems

OpenNTPD may work on other operating systems, newer and older, but the above
ones are tested most recently by the developer. At the time of writing,
OpenNTPD portable is known to build and work on:

 - OpenBSD (6.7)
 - Linux (Debian 10+, Ubuntu 18.04+)
 - FreeBSD (12+)
 - MacOS (10.13+)

Reports (success or otherwise) are welcome. You may report bugs or submit pull
requests at the GitHub project: https://github.com/openntpd-portable
