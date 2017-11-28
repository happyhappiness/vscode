static void
serverConnectionsOpen(void)
{
    clientOpenListenSockets();
    icpConnectionsOpen();
#if USE_HTCP

    htcpInit();
#endif
#ifdef SQUID_SNMP

    snmpConnectionOpen();
#endif
#if USE_WCCP

    wccpConnectionOpen();
#endif

#if USE_WCCPv2

    wccp2ConnectionOpen();
#endif

    clientdbInit();
    icmpEngine.Open();
    netdbInit();
    asnInit();
    ACL::Initialize();
    peerSelectInit();

    carpInit();
    peerUserHashInit();
    peerSourceHashInit();
}