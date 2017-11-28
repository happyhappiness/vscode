static void
serverConnectionsOpen(void)
{
    if (IamPrimaryProcess()) {
#if USE_WCCP
        wccpConnectionOpen();
#endif

#if USE_WCCPv2

        wccp2ConnectionOpen();
#endif
    }
    // start various proxying services if we are responsible for them
    if (IamWorkerProcess()) {
        clientOpenListenSockets();
        icpOpenPorts();
#if USE_HTCP
        htcpOpenPorts();
#endif
#if SQUID_SNMP
        snmpOpenPorts();
#endif

        clientdbInit();
        icmpEngine.Open();
        netdbInit();
        asnInit();
        ACL::Initialize();
        peerSelectInit();

        carpInit();
#if USE_AUTH
        peerUserHashInit();
#endif
        peerSourceHashInit();
    }
}