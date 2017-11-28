static void
commio_set_callback(int fd, iocb_type type, comm_io_callback_t *ccb,
                    AsyncCall::Pointer &cb, char *buf, FREE *freefunc, int size)
{
    assert(!ccb->active());
    assert(ccb->type == type);
    assert(cb != NULL);
    ccb->fd = fd;
    ccb->callback = cb;
    ccb->buf = buf;
    ccb->freefunc = freefunc;
    ccb->size = size;
    ccb->offset = 0;
}