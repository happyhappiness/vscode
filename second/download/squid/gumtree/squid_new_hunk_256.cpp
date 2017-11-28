    mib_tree_last = snmpAddNodeStr("1.3.6.1.4.1.3495.1.5.2.2", MESH_CTBL_ICPHITBYTES, snmp_meshCtblFn, client_Inst);

    debugs(49, 9, "snmpInit: Completed SNMP mib tree structure");
}

void
snmpOpenPorts(void)
{
    debugs(49, 5, "snmpConnectionOpen: Called");

    if (Config.Port.snmp <= 0)
        return;

    snmpIncomingConn = new Comm::Connection;
    snmpIncomingConn->local = Config.Addrs.snmp_incoming;
    snmpIncomingConn->local.SetPort(Config.Port.snmp);

    if (!Ip::EnableIpv6 && !snmpIncomingConn->local.SetIPv4()) {
        debugs(49, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << snmpIncomingConn->local << " is not an IPv4 address.");
        fatal("SNMP port cannot be opened.");
    }
    /* split-stack for now requires IPv4-only SNMP */
    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && snmpIncomingConn->local.IsAnyAddr()) {
        snmpIncomingConn->local.SetIPv4();
    }

    AsyncCall::Pointer call = asyncCall(49, 2, "snmpIncomingConnectionOpened",
                                        Comm::UdpOpenDialer(&snmpPortOpened));
    Ipc::StartListening(SOCK_DGRAM, IPPROTO_UDP, snmpIncomingConn, Ipc::fdnInSnmpSocket, call);

    if (!Config.Addrs.snmp_outgoing.IsNoAddr()) {
        snmpOutgoingConn = new Comm::Connection;
        snmpOutgoingConn->local = Config.Addrs.snmp_outgoing;
        snmpOutgoingConn->local.SetPort(Config.Port.snmp);

        if (!Ip::EnableIpv6 && !snmpOutgoingConn->local.SetIPv4()) {
            debugs(49, DBG_CRITICAL, "ERROR: IPv6 is disabled. " << snmpOutgoingConn->local << " is not an IPv4 address.");
            fatal("SNMP port cannot be opened.");
        }
        /* split-stack for now requires IPv4-only SNMP */
        if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && snmpOutgoingConn->local.IsAnyAddr()) {
            snmpOutgoingConn->local.SetIPv4();
        }
        AsyncCall::Pointer call = asyncCall(49, 2, "snmpOutgoingConnectionOpened",
                                            Comm::UdpOpenDialer(&snmpPortOpened));
        Ipc::StartListening(SOCK_DGRAM, IPPROTO_UDP, snmpOutgoingConn, Ipc::fdnOutSnmpSocket, call);
    } else {
        snmpOutgoingConn = snmpIncomingConn;
        debugs(1, DBG_IMPORTANT, "Sending SNMP messages from " << snmpOutgoingConn->local);
    }
}

static void
snmpPortOpened(const Comm::ConnectionPointer &conn, int errNo)
{
    if (!Comm::IsConnOpen(conn))
        fatalf("Cannot open SNMP %s Port",(conn->fd == snmpIncomingConn->fd?"receiving":"sending"));

    Comm::SetSelect(conn->fd, COMM_SELECT_READ, snmpHandleUdp, NULL, 0);

    if (conn->fd == snmpIncomingConn->fd)
        debugs(1, DBG_IMPORTANT, "Accepting SNMP messages on " << snmpIncomingConn->local);
    else if (conn->fd == snmpOutgoingConn->fd)
        debugs(1, DBG_IMPORTANT, "Sending SNMP messages from " << snmpOutgoingConn->local);
    else
        fatalf("Lost SNMP port (%d) on FD %d", (int)conn->local.GetPort(), conn->fd);
}

void
snmpClosePorts(void)
{
    if (Comm::IsConnOpen(snmpIncomingConn)) {
        debugs(49, DBG_IMPORTANT, "Closing SNMP receiving port " << snmpIncomingConn->local);
        snmpIncomingConn->close();
    }
    snmpIncomingConn = NULL;

    if (Comm::IsConnOpen(snmpOutgoingConn) && snmpIncomingConn != snmpOutgoingConn) {
        // Perform OUT port closure so as not to step on IN port when sharing a conn.
        debugs(49, DBG_IMPORTANT, "Closing SNMP sending port " << snmpOutgoingConn->local);
        snmpOutgoingConn->close();
    }
    snmpOutgoingConn = NULL;
}

/*
 * Functions for handling the requests.
 */

