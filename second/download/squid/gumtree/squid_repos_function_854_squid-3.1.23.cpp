bool
comm_has_incomplete_write(int fd)
{
    assert(isOpen(fd));
    return COMMIO_FD_WRITECB(fd)->active();
}