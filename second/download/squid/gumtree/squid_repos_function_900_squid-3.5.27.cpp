void
comm_set_transparent(int fd)
{
#if _SQUID_LINUX_ && defined(IP_TRANSPARENT) // Linux
# define soLevel SOL_IP
# define soFlag  IP_TRANSPARENT
    bool doneSuid = false;

#elif defined(SO_BINDANY) // OpenBSD 4.7+ and NetBSD with PF
# define soLevel SOL_SOCKET
# define soFlag  SO_BINDANY
    enter_suid();
    bool doneSuid = true;

#elif defined(IP_BINDANY) // FreeBSD with IPFW
# define soLevel IPPROTO_IP
# define soFlag  IP_BINDANY
    enter_suid();
    bool doneSuid = true;

#else
    debugs(50, DBG_CRITICAL, "WARNING: comm_open: setsockopt(TPROXY) not supported on this platform");
#endif /* sockopt */

#if defined(soLevel) && defined(soFlag)
    int tos = 1;
    if (setsockopt(fd, soLevel, soFlag, (char *) &tos, sizeof(int)) < 0) {
        debugs(50, DBG_IMPORTANT, "comm_open: setsockopt(TPROXY) on FD " << fd << ": " << xstrerror());
    } else {
        /* mark the socket as having transparent options */
        fd_table[fd].flags.transparent = true;
    }
    if (doneSuid)
        leave_suid();
#endif
}