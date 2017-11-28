void
comm_set_transparent(int fd)
{
#if !LINUX_TPROXY2
#if defined(IP_TRANSPARENT)
    int tos = 1;
    if (setsockopt(fd, SOL_IP, IP_TRANSPARENT, (char *) &tos, sizeof(int)) < 0) {
        debugs(50, DBG_IMPORTANT, "comm_open: setsockopt(IP_TRANSPARENT) on FD " << fd << ": " << xstrerror());
    } else {
        /* mark the socket as having transparent options */
        fd_table[fd].flags.transparent = 1;
    }
#else
    debugs(50, DBG_CRITICAL, "WARNING: comm_open: setsockopt(IP_TRANSPARENT) not supported on this platform");
#endif /* sockopt */
#endif /* !LINUX_TPROXY2 */
}