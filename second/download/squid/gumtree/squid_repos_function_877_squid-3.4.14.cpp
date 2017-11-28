bool
comm_has_incomplete_write(int fd)
{
    assert(isOpen(fd) && COMMIO_FD_WRITECB(fd));
    return COMMIO_FD_WRITECB(fd)->active();
}