        snmpOutgoingConn = snmpIncomingConn;
        debugs(1, DBG_IMPORTANT, "Sending SNMP messages from " << snmpOutgoingConn->local);
    }
}

static void
snmpPortOpened(const Comm::ConnectionPointer &conn, int)
{
    if (!Comm::IsConnOpen(conn))
        fatalf("Cannot open SNMP %s Port",(conn->fd == snmpIncomingConn->fd?"receiving":"sending"));

    Comm::SetSelect(conn->fd, COMM_SELECT_READ, snmpHandleUdp, NULL, 0);

