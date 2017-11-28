static void
commio_cancel_callback(int fd, comm_io_callback_t *ccb)
{
    debugs(5, 3, "commio_cancel_callback: called for FD " << fd);
    assert(ccb->fd == fd);
    assert(ccb->active());

    ccb->xerrno = 0;
    ccb->callback = NULL;
}