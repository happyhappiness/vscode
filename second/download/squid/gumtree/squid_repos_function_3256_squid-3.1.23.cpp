void
snmpConnectionClose(void)
{
    snmpConnectionShutdown();

    if (theOutSnmpConnection > -1) {
        debugs(49, 1, "FD " << theOutSnmpConnection << " Closing SNMP socket");
        comm_close(theOutSnmpConnection);
        /* make sure the SNMP out connection is unset */
        theOutSnmpConnection = -1;
    }
}