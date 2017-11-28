void
icpConnectionShutdown(void)
{
    if (!Comm::IsConnOpen(icpIncomingConn))
        return;

    debugs(12, DBG_IMPORTANT, "Stop receiving ICP on " << icpIncomingConn->local);

    /** Release the 'in' socket for lazy closure.
     * in and out sockets may be sharing one same FD.
     * This prevents this function from executing repeatedly.
     */
    icpIncomingConn = NULL;

    /**
     * Normally we only write to the outgoing ICP socket, but
     * we also have a read handler there to catch messages sent
     * to that specific interface.  During shutdown, we must
     * disable reading on the outgoing socket.
     */
    assert(Comm::IsConnOpen(icpOutgoingConn));

    Comm::SetSelect(icpOutgoingConn->fd, COMM_SELECT_READ, NULL, NULL, 0);
}