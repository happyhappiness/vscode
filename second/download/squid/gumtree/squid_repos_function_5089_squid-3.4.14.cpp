void
Comm::ResetSelect(int fd)
{
    fde *F = &fd_table[fd];
    F->epoll_state = 0;
    SetSelect(fd, 0, NULL, NULL, 0);
}