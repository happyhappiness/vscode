static void
mainReconfigureStart(void)
{
    if (AvoidSignalAction("reconfiguration", do_reconfigure))
        return;

    debugs(1, DBG_IMPORTANT, "Reconfiguring Squid Cache (version " << version_string << ")...");
    reconfiguring = 1;

    RunRegisteredHere(RegisteredRunner::startReconfigure);

    // Initiate asynchronous closing sequence
    serverConnectionsClose();
    icpClosePorts();
#if USE_HTCP
    htcpClosePorts();
#endif
#if USE_SSL_CRTD
    Ssl::Helper::GetInstance()->Shutdown();
#endif
#if USE_OPENSSL
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