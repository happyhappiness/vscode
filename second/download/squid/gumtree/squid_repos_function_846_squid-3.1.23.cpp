static void
comm_empty_os_read_buffers(int fd)
{
#ifdef _SQUID_LINUX_
    /* prevent those nasty RST packets */
    char buf[SQUID_TCP_SO_RCVBUF];

    if (fd_table[fd].flags.nonblocking == 1) {
        while (FD_READ_METHOD(fd, buf, SQUID_TCP_SO_RCVBUF) > 0) {};
    }
#endif
}