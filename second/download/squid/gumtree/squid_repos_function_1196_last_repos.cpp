static void
mainInitialize(void)
{
    /* chroot if configured to run inside chroot */
    mainSetCwd();

    if (opt_catch_signals) {
        squid_signal(SIGSEGV, death, SA_NODEFER | SA_RESETHAND);
        squid_signal(SIGBUS, death, SA_NODEFER | SA_RESETHAND);
    }

    squid_signal(SIGPIPE, SIG_IGN, SA_RESTART);
    squid_signal(SIGCHLD, sig_child, SA_NODEFER | SA_RESTART);
    squid_signal(SIGHUP, reconfigure, SA_RESTART);

    setEffectiveUser();

    if (icpPortNumOverride != 1)
        Config.Port.icp = (unsigned short) icpPortNumOverride;

    _db_init(Debug::cache_log, Debug::debugOptions);

    fd_open(fileno(debug_log), FD_LOG, Debug::cache_log);

    debugs(1, DBG_CRITICAL, "Starting Squid Cache version " << version_string << " for " << CONFIG_HOST_TYPE << "...");
    debugs(1, DBG_CRITICAL, "Service Name: " << service_name);

#if _SQUID_WINDOWS_
    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        debugs(1, DBG_CRITICAL, "Service command line is: " << WIN32_Service_Command_Line);
    } else
        debugs(1, DBG_CRITICAL, "Running on " << WIN32_OS_string);
#endif

    debugs(1, DBG_IMPORTANT, "Process ID " << getpid());

    debugs(1, DBG_IMPORTANT, "Process Roles:" << ProcessRoles());

    setSystemLimits();
    debugs(1, DBG_IMPORTANT, "With " << Squid_MaxFD << " file descriptors available");

#if _SQUID_WINDOWS_

    debugs(1, DBG_IMPORTANT, "With " << _getmaxstdio() << " CRT stdio descriptors available");

    if (WIN32_Socks_initialized)
        debugs(1, DBG_IMPORTANT, "Windows sockets initialized");

    if (WIN32_OS_version > _WIN_OS_WINNT) {
        WIN32_IpAddrChangeMonitorInit();
    }

#endif

    ipcache_init();

    fqdncache_init();

    parseEtcHosts();

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

    httpHeaderInitModule(); /* must go before any header processing (e.g. the one in errorInitialize) */

    errorInitialize();

    accessLogInit();

#if ICAP_CLIENT
    icapLogOpen();
#endif

#if USE_IDENT
    Ident::Init();
#endif

#if SQUID_SNMP

    snmpInit();

#endif
#if MALLOC_DBG

    malloc_debug(0, malloc_debug_level);

#endif

    if (!configured_once) {
        if (unlinkdNeeded())
            unlinkdInit();

        urlInitialize();
        statInit();
        storeInit();
        mainSetCwd();
        mimeInit(Config.mimeTablePathname);
        refreshInit();
#if USE_DELAY_POOLS
        DelayPools::Init();
#endif

        FwdState::initModule();
        /* register the modules in the cache manager menus */

        cbdataRegisterWithCacheManager();
        SBufStatsAction::RegisterWithCacheManager();

        /* These use separate calls so that the comm loops can eventually
         * coexist.
         */

        eventInit();

        // TODO: pconn is a good candidate for new-style registration
        // PconnModule::GetInstance()->registerWithCacheManager();
        //   moved to PconnModule::PconnModule()
    }

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

    // neighborsRegisterWithCacheManager(); //moved to neighbors_init()

    if (Config.chroot_dir)
        no_suid();

#if defined(_SQUID_LINUX_THREADS_)

    squid_signal(SIGQUIT, rotate_logs, SA_RESTART);

    squid_signal(SIGTRAP, sigusr2_handle, SA_RESTART);

#else

    squid_signal(SIGUSR1, rotate_logs, SA_RESTART);

    squid_signal(SIGUSR2, sigusr2_handle, SA_RESTART);

#endif

    squid_signal(SIGTERM, shut_down, SA_RESTART);

    squid_signal(SIGINT, shut_down, SA_RESTART);

#ifdef SIGTTIN

    squid_signal(SIGTTIN, shut_down, SA_RESTART);

#endif

    memCheckInit();

#if USE_LOADABLE_MODULES
    LoadableModulesConfigure(Config.loadable_module_names);
#endif

#if USE_ADAPTATION
    bool enableAdaptation = false;

    // We can remove this dependency on specific adaptation mechanisms
    // if we create a generic Registry of such mechanisms. Should we?
#if ICAP_CLIENT
    Adaptation::Icap::TheConfig.finalize();
    enableAdaptation = Adaptation::Icap::TheConfig.onoff || enableAdaptation;
#endif
#if USE_ECAP
    Adaptation::Ecap::TheConfig.finalize(); // must be after we load modules
    enableAdaptation = Adaptation::Ecap::TheConfig.onoff || enableAdaptation;
#endif
    // must be the last adaptation-related finalize
    Adaptation::Config::Finalize(enableAdaptation);
#endif

#if USE_SQUID_ESI
    Esi::Init();
#endif

#if USE_DELAY_POOLS
    Config.ClientDelay.finalize();
#endif

    if (!configured_once) {
        eventAdd("storeMaintain", Store::Maintain, NULL, 1.0, 1);

        if (Config.onoff.announce)
            eventAdd("start_announce", start_announce, NULL, 3600.0, 1);

        eventAdd("ipcache_purgelru", ipcache_purgelru, NULL, 10.0, 1);

        eventAdd("fqdncache_purgelru", fqdncache_purgelru, NULL, 15.0, 1);

#if USE_XPROF_STATS

        eventAdd("cpuProfiling", xprof_event, NULL, 1.0, 1);

#endif

        eventAdd("memPoolCleanIdlePools", Mem::CleanIdlePools, NULL, 15.0, 1);
    }

    configured_once = 1;
}