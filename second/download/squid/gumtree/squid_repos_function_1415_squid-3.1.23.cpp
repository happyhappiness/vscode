static void
mainReconfigureStart(void)
{
    debugs(1, 1, "Reconfiguring Squid Cache (version " << version_string << ")...");
    reconfiguring = 1;

    // Initiate asynchronous closing sequence
    serverConnectionsClose();
    icpConnectionClose();
#if USE_HTCP

    htcpSocketClose();
#endif
#ifdef SQUID_SNMP

    snmpConnectionClose();
#endif
#if USE_DNSSERVERS

    dnsShutdown();
#else

    idnsShutdown();
#endif
#if USE_SSL_CRTD
    Ssl::Helper::GetInstance()->Shutdown();
#endif
#if USE_SSL
    Ssl::TheGlobalContextStorage.reconfigureStart();
#endif
    redirectShutdown();
    authenticateShutdown();
    externalAclShutdown();
    storeDirCloseSwapLogs();
    storeLogClose();
    accessLogClose();
#if ICAP_CLIENT
    icapLogClose();
#endif
    useragentLogClose();
    refererCloseLog();

    eventAdd("mainReconfigureFinish", &mainReconfigureFinish, NULL, 0, 1,
             false);
}