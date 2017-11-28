void
Comm::TcpAcceptor::acceptOne()
{
    /*
     * We don't worry about running low on FDs here.  Instead,
     * doAccept() will use AcceptLimiter if we reach the limit
     * there.
     */

    /* Accept a new connection */
    ConnectionPointer newConnDetails = new Connection();
    const comm_err_t flag = oldAccept(newConnDetails);

    /* Check for errors */
    if (!newConnDetails->isOpen()) {

        if (flag == COMM_NOMESSAGE) {
            /* register interest again */
            debugs(5, 5, HERE << "try later: " << conn << " handler Subscription: " << theCallSub);
            SetSelect(conn->fd, COMM_SELECT_READ, doAccept, this, 0);
            return;
        }

        // A non-recoverable error; notify the caller */
        debugs(5, 5, HERE << "non-recoverable error:" << status() << " handler Subscription: " << theCallSub);
        notify(flag, newConnDetails);
        mustStop("Listener socket closed");
        return;
    }

    debugs(5, 5, HERE << "Listener: " << conn <<
           " accepted new connection " << newConnDetails <<
           " handler Subscription: " << theCallSub);
    notify(flag, newConnDetails);
}