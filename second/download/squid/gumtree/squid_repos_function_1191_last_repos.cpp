static void
mainReconfigureFinish(void *)
{
    debugs(1, 3, "finishing reconfiguring");

    errorClean();
    enter_suid();       /* root to read config file */

    // we may have disabled the need for PURGE
    if (Config2.onoff.enable_purge)
        Config2.onoff.enable_purge = 2;

    // parse the config returns a count of errors encountered.
    const int oldWorkers = Config.workers;
    try {
        if (parseConfigFile(ConfigFile) != 0) {
            // for now any errors are a fatal condition...
            self_destruct();
        }
    } catch (...) {
        // for now any errors are a fatal condition...
        debugs(1, DBG_CRITICAL, "FATAL: Unhandled exception parsing config file. " <<
               " Run squid -k parse and check for errors.");
        self_destruct();
    }

    if (oldWorkers != Config.workers) {
        debugs(1, DBG_CRITICAL, "WARNING: Changing 'workers' (from " <<
               oldWorkers << " to " << Config.workers <<
               ") requires a full restart. It has been ignored by reconfigure.");
        Config.workers = oldWorkers;
    }

    RunRegisteredHere(RegisteredRunner::syncConfig);

    if (IamPrimaryProcess())
        CpuAffinityCheck();
    CpuAffinityReconfigure();

    setUmask(Config.umask);
    Mem::Report();
    setEffectiveUser();
    _db_init(Debug::cache_log, Debug::debugOptions);
    ipcache_restart();      /* clear stuck entries */
    fqdncache_restart();    /* sigh, fqdncache too */
    parseEtcHosts();
    errorInitialize();      /* reload error pages */
    accessLogInit();

#if USE_LOADABLE_MODULES
    LoadableModulesConfigure(Config.loadable_module_names);
#endif

#if USE_ADAPTATION
    bool enableAdaptation = false;
#if ICAP_CLIENT
    Adaptation::Icap::TheConfig.finalize();
    enableAdaptation = Adaptation::Icap::TheConfig.onoff || enableAdaptation;
#endif
#if USE_ECAP
    Adaptation::Ecap::TheConfig.finalize(); // must be after we load modules
    enableAdaptation = Adaptation::Ecap::TheConfig.onoff || enableAdaptation;
#endif
    Adaptation::Config::Finalize(enableAdaptation);
#endif

#if ICAP_CLIENT
    icapLogOpen();
#endif
    storeLogOpen();
    Dns::Init();
#if USE_SSL_CRTD
    Ssl::Helper::GetInstance()->Init();
#endif
#if USE_OPENSSL
    if (Ssl::CertValidationHelper::GetInstance())
        Ssl::CertValidationHelper::GetInstance()->Init();
#endif

    redirectInit();
#if USE_AUTH
    authenticateInit(&Auth::TheConfig);
#endif
    externalAclInit();

    if (IamPrimaryProcess()) {
#if USE_WCCP

        wccpInit();
#endif
#if USE_WCCPv2

        wccp2Init();
#endif
    }

    serverConnectionsOpen();

    neighbors_init();

    storeDirOpenSwapLogs();

    mimeInit(Config.mimeTablePathname);

    if (unlinkdNeeded())
        unlinkdInit();

#if USE_DELAY_POOLS
    Config.ClientDelay.finalize();
#endif

    if (Config.onoff.announce) {
        if (!eventFind(start_announce, NULL))
            eventAdd("start_announce", start_announce, NULL, 3600.0, 1);
    } else {
        if (eventFind(start_announce, NULL))
            eventDelete(start_announce, NULL);
    }

    reconfiguring = 0;
}