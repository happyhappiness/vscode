void
htcpSocketShutdown(void)
{
    if (htcpInSocket < 0)
        return;

    if (htcpInSocket != htcpOutSocket) {
        debugs(12, 1, "FD " << htcpInSocket << " Closing HTCP socket");
        comm_close(htcpInSocket);
    }

    /*
     * Here we set 'htcpInSocket' to -1 even though the HTCP 'in'
     * and 'out' sockets might be just one FD.  This prevents this
     * function from executing repeatedly.  When we are really ready to
     * exit or restart, main will comm_close the 'out' descriptor.
     */
    htcpInSocket = -1;

    /*
     * Normally we only write to the outgoing HTCP socket, but
     * we also have a read handler there to catch messages sent
     * to that specific interface.  During shutdown, we must
     * disable reading on the outgoing socket.
     */
    /* XXX Don't we need this handler to read replies while shutting down?
     * I think there should be a separate hander for reading replies..
     */
    assert(htcpOutSocket > -1);

    commSetSelect(htcpOutSocket, COMM_SELECT_READ, NULL, NULL, 0);
}