
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

