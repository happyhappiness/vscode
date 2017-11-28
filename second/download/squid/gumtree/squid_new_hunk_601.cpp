
    if (conn->fd == snmpIncomingConn->fd)
        debugs(1, DBG_IMPORTANT, "Accepting SNMP messages on " << snmpIncomingConn->local);
    else if (conn->fd == snmpOutgoingConn->fd)
        debugs(1, DBG_IMPORTANT, "Sending SNMP messages from " << snmpOutgoingConn->local);
    else
        fatalf("Lost SNMP port (%d) on FD %d", (int)conn->local.port(), conn->fd);
}

void
snmpClosePorts(void)
{
    if (Comm::IsConnOpen(snmpIncomingConn)) {
