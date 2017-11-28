void
fd_close(int fd)
{
    close(fd);
    if (FD[fd].ccb)
        FD[fd].ccb(fd, FD[fd].data);
    FD[fd].ccb = NULL;
    FD[fd].cb = NULL;
    FD[fd].data = NULL;
    nfds--;
    if (fd == maxfd) {
        while (fd > 0 && FD[fd].cb == NULL)
            fd--;
        maxfd = fd;
    }
}