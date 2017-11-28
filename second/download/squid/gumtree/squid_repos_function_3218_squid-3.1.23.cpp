void
IdleConnList::clearHandlers(int fd)
{
    comm_read_cancel(fd, IdleConnList::read, this);
    commSetTimeout(fd, -1, NULL, NULL);
}