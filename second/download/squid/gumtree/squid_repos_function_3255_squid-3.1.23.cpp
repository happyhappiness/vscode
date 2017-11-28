void
snmpConnectionShutdown(void)
{
    if (theInSnmpConnection < 0)
        return;

    if (theInSnmpConnection != theOutSnmpConnection) {
        debugs(49, 1, "FD " << theInSnmpConnection << " Closing SNMP socket");
        comm_close(theInSnmpConnection);
    }

    /*
     * Here we set 'theInSnmpConnection' to -1 even though the SNMP 'in'
     * and 'out' sockets might be just one FD.  This prevents this
     * function from executing repeatedly.  When we are really ready to
     * exit or restart, main will comm_close the 'out' descriptor.
     */
    theInSnmpConnection = -1;

    /*
     * Normally we only write to the outgoing SNMP socket, but we
     * also have a read handler there to catch messages sent to that
     * specific interface.  During shutdown, we must disable reading
     * on the outgoing socket.
     */
    assert(theOutSnmpConnection > -1);

    commSetSelect(theOutSnmpConnection, COMM_SELECT_READ, NULL, NULL, 0);
}