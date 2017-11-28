void
Comm::ReadCancel(int fd, AsyncCall::Pointer &callback)
{
    callback->cancel("comm_read_cancel");

    if (!isOpen(fd)) {
        debugs(5, 4, "fails: FD " << fd << " closed");
        return;
    }

    Comm::IoCallback *cb = COMMIO_FD_READCB(fd);

    if (!cb->active()) {
        debugs(5, 4, "fails: FD " << fd << " inactive");
        return;
    }

    AsyncCall::Pointer call = cb->callback;

    /* Ok, we can be reasonably sure we won't lose any data here! */
    assert(call == callback);

    /* Delete the callback */
    cb->cancel("comm_read_cancel");

    /* And the IO event */
    Comm::SetSelect(fd, COMM_SELECT_READ, NULL, NULL, 0);
}