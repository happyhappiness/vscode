static void
serverConnectionsClose(void)
{
    assert(shutting_down || reconfiguring);
    clientHttpConnectionsClose();
    icpConnectionShutdown();
#if USE_HTCP

    htcpSocketShutdown();
#endif

    icmpEngine.Close();
#ifdef SQUID_SNMP

    snmpConnectionShutdown();
#endif
#if USE_WCCP

    wccpConnectionClose();
#endif
#if USE_WCCPv2

    wccp2ConnectionClose();
#endif

    asnFreeMemory();
}