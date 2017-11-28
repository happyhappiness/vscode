void
comm_remove_close_handler(int fd, PF * handler, void *data)
{
    assert (isOpen(fd));
    /* Find handler in list */
    debugs(5, 5, "comm_remove_close_handler: FD " << fd << ", handler=" <<
           handler << ", data=" << data);

    AsyncCall::Pointer p, prev = NULL;
    for (p = fd_table[fd].closeHandler; p != NULL; prev = p, p = p->Next()) {
        typedef CommCbFunPtrCallT<CommCloseCbPtrFun> Call;
        const Call *call = dynamic_cast<const Call*>(p.getRaw());
        if (!call) // method callbacks have their own comm_remove_close_handler
            continue;

        typedef CommCloseCbParams Params;
        const Params &params = GetCommParams<Params>(p);
        if (call->dialer.handler == handler && params.data == data)
            break;		/* This is our handler */
    }

    // comm_close removes all close handlers so our handler may be gone
    if (p != NULL) {
        p->dequeue(fd_table[fd].closeHandler, prev);
        p->cancel("comm_remove_close_handler");
    }
}