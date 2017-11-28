void
comm_remove_close_handler(int fd, AsyncCall::Pointer &call)
{
    assert (isOpen(fd));
    debugs(5, 5, "comm_remove_close_handler: FD " << fd << ", AsyncCall=" << call);

    // comm_close removes all close handlers so our handler may be gone
    AsyncCall::Pointer p, prev = NULL;
    for (p = fd_table[fd].closeHandler; p != NULL && p != call; prev = p, p = p->Next());

    if (p != NULL)
        p->dequeue(fd_table[fd].closeHandler, prev);
    call->cancel("comm_remove_close_handler");
}