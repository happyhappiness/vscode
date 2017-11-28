static void
mainReconfigureStart(void)
{
    debugs(1, DBG_IMPORTANT, "Reconfiguring Squid Cache (version " << version_string << ")...");
    reconfiguring = 1;

    // Initiate asynchronous closing sequence
    serverConnectionsClose();
    icpClosePorts();
#if USE_HTCP
    htcpClosePorts();
#endif
    dnsShutdown();
#if USE_SSL_CRTD
    Ssl::Helper::GetInstance()->Shutdown();
#endif
#if USE_SSL
    if (Ssl::CertValidationHelper::GetInstance())
        Ssl::CertValidationHelper::GetInstance()->Shutdown();
    Ssl::TheGlobalContextStorage.reconfigureStart();
#endif
    redirectShutdown();
#if USE_AUTH
    authenticateReset();
#endif
    externalAclShutdown();
    storeDirCloseSwapLogs();
    storeLogClose();
    accessLogClose();
#if ICAP_CLIENT
    icapLogClose();
#endif

    eventAdd("mainReconfigureFinish", &mainReconfigureFinish, NULL, 0, 1,
             false);
}