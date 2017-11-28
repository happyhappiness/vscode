void
commResetSelect(int fd)
{
    fde *F = &fd_table[fd];
    F->epoll_state = 0;
    commSetSelect(fd, 0, NULL, NULL, 0);
}