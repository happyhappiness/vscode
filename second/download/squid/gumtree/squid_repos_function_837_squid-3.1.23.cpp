bool
commio_has_callback(int fd, iocb_type type, comm_io_callback_t *ccb)
{
    assert(ccb->fd == fd);
    assert(ccb->type == type);
    return ccb->active();
}