void
commUpdateReadBits(int fd, PF * handler)
{
    if (handler && !FD_ISSET(fd, &global_readfds)) {
        FD_SET(fd, &global_readfds);
        ++nreadfds;
    } else if (!handler && FD_ISSET(fd, &global_readfds)) {
        FD_CLR(fd, &global_readfds);
        --nreadfds;
    }
}