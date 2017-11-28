static void
mainReconfigureFinish(void *)
{
    debugs(1, 3, "finishing reconfiguring");

    errorClean();
    enter_suid();		/* root to read config file */

    // we may have disabled the need for PURGE
    if (Config2.onoff.enable_purge)
        Config2.onoff.enable_purge = 2;

    // parse the config returns a count of errors encountered.
    if ( parseConfigFile(ConfigFile) != 0) {
        // for now any errors are a fatal condition...
        self_destruct();
    }

    setUmask(Config.umask);
    Mem::Report();
    setEffectiveUser();
    _db_init(Debug::cache_log, Debug::debugOptions);
    ipcache_restart();		/* clear stuck entries */
    authenticateUserCacheRestart();	/* clear stuck ACL entries */
    fqdncache_restart();	/* sigh, fqdncache too */
    parseEtcHosts();
    errorInitialize();		/* reload error pages */
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
    useragentOpenLog();
    refererOpenLog();
#if USE_DNSSERVERS

    dnsInit();
#else

    idnsInit();
#endif
#if USE_SSL_CRTD
    Ssl::Helper::GetInstance()->Init();
#endif

    redirectInit();
    authenticateInit(&Config.authConfiguration);
    externalAclInit();
#if USE_WCCP

    wccpInit();
#endif
#if USE_WCCPv2

    wccp2Init();
#endif

    serverConnectionsOpen();

    neighbors_init();

    storeDirOpenSwapLogs();

    mimeInit(Config.mimeTablePathname);

    if (Config.onoff.announce) {
        if (!eventFind(start_announce, NULL))
            eventAdd("start_announce", start_announce, NULL, 3600.0, 1);
    } else {
        if (eventFind(start_announce, NULL))
            eventDelete(start_announce, NULL);
    }

    writePidFile();		/* write PID file */

    debugs(1, 1, "Ready to serve requests.");

    reconfiguring = 0;
}