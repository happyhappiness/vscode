void
icpConnectionShutdown(void)
{
    if (theInIcpConnection < 0)
        return;

    if (theInIcpConnection != theOutIcpConnection) {
        debugs(12, 1, "FD " << theInIcpConnection << " Closing ICP connection");
        comm_close(theInIcpConnection);
    }

    /**
     * Here we set 'theInIcpConnection' to -1 even though the ICP 'in'
     * and 'out' sockets might be just one FD.  This prevents this
     * function from executing repeatedly.  When we are really ready to
     * exit or restart, main will comm_close the 'out' descriptor.
     */
    theInIcpConnection = -1;

    /**
     * Normally we only write to the outgoing ICP socket, but
     * we also have a read handler there to catch messages sent
     * to that specific interface.  During shutdown, we must
     * disable reading on the outgoing socket.
     */
    assert(theOutIcpConnection > -1);

    commSetSelect(theOutIcpConnection, COMM_SELECT_READ, NULL, NULL, 0);
}