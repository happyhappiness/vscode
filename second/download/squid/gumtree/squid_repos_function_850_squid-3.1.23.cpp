void
comm_read_cancel(int fd, AsyncCall::Pointer &callback)
{
    callback->cancel("comm_read_cancel");

    if (!isOpen(fd)) {
        debugs(5, 4, "comm_read_cancel fails: FD " << fd << " closed");
        return;
    }

    comm_io_callback_t *cb = COMMIO_FD_READCB(fd);

    if (!cb->active()) {
        debugs(5, 4, "comm_read_cancel fails: FD " << fd << " inactive");
        return;
    }

    AsyncCall::Pointer call = cb->callback;
    assert(call != NULL); // XXX: should never fail (active() checks for callback==NULL)

    /* Ok, we can be reasonably sure we won't lose any data here! */
    assert(call == callback);

    /* Delete the callback */
    commio_cancel_callback(fd, cb);

    /* And the IO event */
    commSetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
}