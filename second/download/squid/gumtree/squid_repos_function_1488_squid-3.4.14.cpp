static void
serverConnectionsClose(void)
{
    assert(shutting_down || reconfiguring);

    if (IamPrimaryProcess()) {
#if USE_WCCP

        wccpConnectionClose();
#endif
#if USE_WCCPv2

        wccp2ConnectionClose();
#endif
    }
    if (IamWorkerProcess()) {
        clientHttpConnectionsClose();
        icpConnectionShutdown();
#if USE_HTCP
        htcpSocketShutdown();
#endif

        icmpEngine.Close();
#if SQUID_SNMP
        snmpClosePorts();
#endif

        asnFreeMemory();
    }
}