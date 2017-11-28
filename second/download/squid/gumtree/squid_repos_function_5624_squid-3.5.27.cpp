void
commUpdateWriteBits(int fd, PF * handler)
{
    if (handler && !FD_ISSET(fd, &global_writefds)) {
        FD_SET(fd, &global_writefds);
        ++nwritefds;
    } else if (!handler && FD_ISSET(fd, &global_writefds)) {
        FD_CLR(fd, &global_writefds);
        --nwritefds;
    }
}