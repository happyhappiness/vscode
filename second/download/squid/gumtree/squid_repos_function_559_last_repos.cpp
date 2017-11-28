static void
comm_empty_os_read_buffers(int fd)
{
#if _SQUID_LINUX_
#if USE_OPENSSL
    // Bug 4146: SSL-Bump BIO does not release sockets on close.
    if (fd_table[fd].ssl)
        return;
#endif

    /* prevent those nasty RST packets */
    char buf[SQUID_TCP_SO_RCVBUF];
    if (fd_table[fd].flags.nonblocking && fd_table[fd].type != FD_MSGHDR) {
        while (FD_READ_METHOD(fd, buf, SQUID_TCP_SO_RCVBUF) > 0) {};
    }
#endif
}