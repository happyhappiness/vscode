static void
commio_finish_callback(int fd, comm_io_callback_t *ccb, comm_err_t code, int xerrno)
{
    debugs(5, 3, "commio_finish_callback: called for FD " << fd << " (" <<
           code << ", " << xerrno << ")");
    assert(ccb->active());
    assert(ccb->fd == fd);
    ccb->errcode = code;
    ccb->xerrno = xerrno;

    comm_io_callback_t cb = *ccb;

    /* We've got a copy; blow away the real one */
    /* XXX duplicate code from commio_cancel_callback! */
    ccb->xerrno = 0;
    ccb->callback = NULL; // cb has it

    /* free data */
    if (cb.freefunc) {
        cb.freefunc(cb.buf);
        cb.buf = NULL;
    }

    if (cb.callback != NULL) {
        typedef CommIoCbParams Params;
        Params &params = GetCommParams<Params>(cb.callback);
        params.fd = cb.fd;
        params.buf = cb.buf;
        params.size = cb.offset;
        params.flag = cb.errcode;
        params.xerrno = cb.xerrno;
        ScheduleCallHere(cb.callback);
    }
}