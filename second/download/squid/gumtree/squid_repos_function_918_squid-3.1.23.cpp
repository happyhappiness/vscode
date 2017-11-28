void
AcceptFD::acceptOne()
{
    // If there is no callback and we accept, we will leak the accepted FD.
    // When we are running out of FDs, there is often no callback.
    if (!theCallback) {
        debugs(5, 5, "AcceptFD::acceptOne orphaned: FD " << fd);
        // XXX: can we remove this and similar "just in case" calls and
        // either listen always or listen only when there is a callback?
        if (!AcceptLimiter::Instance().deferring())
            commSetSelect(fd, COMM_SELECT_READ, comm_accept_try, NULL, 0);
        mayAcceptMore = false;
        return;
    }

    /*
     * We don't worry about running low on FDs here.  Instead,
     * httpAccept() will use AcceptLimiter if we reach the limit
     * there.
     */

    /* Accept a new connection */
    ConnectionDetail connDetails;
    int newfd = comm_old_accept(fd, connDetails);

    /* Check for errors */

    if (newfd < 0) {
        assert(theCallback != NULL);

        if (newfd == COMM_NOMESSAGE) {
            /* register interest again */
            debugs(5, 5, HERE << "try later: FD " << fd <<
                   " handler: " << theCallback);
            commSetSelect(fd, COMM_SELECT_READ, comm_accept_try, NULL, 0);
            return;
        }

        // A non-recoverable error; notify the caller */
        notify(-1, COMM_ERROR, errno, connDetails);
        mayAcceptMore = false;
        return;
    }

    assert(theCallback != NULL);
    debugs(5, 5, "AcceptFD::acceptOne accepted: FD " << fd <<
           " newfd: " << newfd << " from: " << connDetails.peer <<
           " handler: " << *theCallback);
    notify(newfd, COMM_OK, 0, connDetails);
    mayAcceptMore = true;
}