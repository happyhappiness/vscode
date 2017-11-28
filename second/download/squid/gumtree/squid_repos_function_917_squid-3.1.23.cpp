void
AcceptFD::subscribe(AsyncCall::Pointer &call)
{
    /* make sure we're not pending! */
    assert(!theCallback);
    theCallback = call;

#if OPTIMISTIC_IO
    mayAcceptMore = true; // even if we failed to accept last time
#endif

    if (mayAcceptMore)
        acceptNext();
    else
        commSetSelect(fd, COMM_SELECT_READ, comm_accept_try, NULL, 0);
}