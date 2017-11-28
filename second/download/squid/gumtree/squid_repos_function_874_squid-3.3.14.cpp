void
comm_set_transparent(int fd)
{
#if _SQUID_LINUX_ && defined(IP_TRANSPARENT)
    int tos = 1;
    if (setsockopt(fd, SOL_IP, IP_TRANSPARENT, (char *) &tos, sizeof(int)) < 0) {
        debugs(50, DBG_IMPORTANT, "comm_open: setsockopt(IP_TRANSPARENT) on FD " << fd << ": " << xstrerror());
    } else {
        /* mark the socket as having transparent options */
        fd_table[fd].flags.transparent = 1;
    }

#elif defined(SO_BINDANY)
    int tos = 1;
    enter_suid();
    if (setsockopt(fd, SOL_SOCKET, SO_BINDANY, (char *) &tos, sizeof(int)) < 0) {
        debugs(50, DBG_IMPORTANT, "comm_open: setsockopt(SO_BINDANY) on FD " << fd << ": " << xstrerror());
    } else {
        /* mark the socket as having transparent options */
        fd_table[fd].flags.transparent = true;
    }
    leave_suid();

#else
    debugs(50, DBG_CRITICAL, "WARNING: comm_open: setsockopt(IP_TRANSPARENT) not supported on this platform");
#endif /* sockopt */
}