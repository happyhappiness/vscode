void
comm_read_cancel(int fd, IOCB *callback, void *data)
{
    if (!isOpen(fd)) {
        debugs(5, 4, "comm_read_cancel fails: FD " << fd << " closed");
        return;
    }

    comm_io_callback_t *cb = COMMIO_FD_READCB(fd);
    // TODO: is "active" == "monitors FD"?
    if (!cb->active()) {
        debugs(5, 4, "comm_read_cancel fails: FD " << fd << " inactive");
        return;
    }

    typedef CommCbFunPtrCallT<CommIoCbPtrFun> Call;
    Call *call = dynamic_cast<Call*>(cb->callback.getRaw());
    if (!call) {
        debugs(5, 4, "comm_read_cancel fails: FD " << fd << " lacks callback");
        return;
    }

    call->cancel("old comm_read_cancel");

    typedef CommIoCbParams Params;
    const Params &params = GetCommParams<Params>(cb->callback);

    /* Ok, we can be reasonably sure we won't lose any data here! */
    assert(call->dialer.handler == callback);
    assert(params.data == data);

    /* Delete the callback */
    commio_cancel_callback(fd, cb);

    /* And the IO event */
    commSetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
}