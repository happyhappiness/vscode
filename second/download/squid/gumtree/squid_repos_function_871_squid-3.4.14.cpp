bool
comm_monitors_read(int fd)
{
    assert(isOpen(fd) && COMMIO_FD_READCB(fd));
    // Being active is usually the same as monitoring because we always
    // start monitoring the FD when we configure Comm::IoCallback for I/O
    // and we usually configure Comm::IoCallback for I/O when we starting
    // monitoring a FD for reading.
    return COMMIO_FD_READCB(fd)->active();
}