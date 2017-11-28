void
htcpSocketShutdown(void)
{
    if (!Comm::IsConnOpen(htcpIncomingConn))
        return;

    debugs(12, DBG_IMPORTANT, "Stop accepting HTCP on " << htcpIncomingConn->local);
    /*
     * Here we just unlink htcpIncomingConn because the HTCP 'in'
     * and 'out' sockets might be just one FD.  This prevents this
     * function from executing repeatedly.  When we are really ready to
     * exit or restart, main will comm_close the 'out' descriptor.
     */
    htcpIncomingConn = NULL;

    /*
     * Normally we only write to the outgoing HTCP socket, but
     * we also have a read handler there to catch messages sent
     * to that specific interface.  During shutdown, we must
     * disable reading on the outgoing socket.
     */
    /* XXX Don't we need this handler to read replies while shutting down?
     * I think there should be a separate hander for reading replies..
     */
    assert(Comm::IsConnOpen(htcpOutgoingConn));

    Comm::SetSelect(htcpOutgoingConn->fd, COMM_SELECT_READ, NULL, NULL, 0);
}