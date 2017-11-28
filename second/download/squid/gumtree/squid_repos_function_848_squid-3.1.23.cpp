bool
comm_monitors_read(int fd)
{
    assert(isOpen(fd));
    // Being active is usually the same as monitoring because we always
    // start monitoring the FD when we configure comm_io_callback_t for I/O
    // and we usually configure comm_io_callback_t for I/O when we starting
    // monitoring a FD for reading. TODO: replace with commio_has_callback
    return COMMIO_FD_READCB(fd)->active();
}