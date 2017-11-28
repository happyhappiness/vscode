static void
mainInitialize(void)
{
    /* chroot if configured to run inside chroot */

    if (Config.chroot_dir && (chroot(Config.chroot_dir) != 0 || chdir("/") != 0)) {
        fatal("failed to chroot");
    }

    if (opt_catch_signals) {
        squid_signal(SIGSEGV, death, SA_NODEFER | SA_RESETHAND);
        squid_signal(SIGBUS, death, SA_NODEFER | SA_RESETHAND);
    }

    squid_signal(SIGPIPE, SIG_IGN, SA_RESTART);
    squid_signal(SIGCHLD, sig_child, SA_NODEFER | SA_RESTART);

    setEffectiveUser();

    if (icpPortNumOverride != 1)
        Config.Port.icp = (unsigned short) icpPortNumOverride;

    _db_init(Debug::cache_log, Debug::debugOptions);

    fd_open(fileno(debug_log), FD_LOG, Debug::cache_log);

#if MEM_GEN_TRACE

    log_trace_init("/tmp/squid.alloc");

#endif

    debugs(1, 0, "Starting Squid Cache version " << version_string << " for " << CONFIG_HOST_TYPE << "...");

#ifdef _SQUID_WIN32_

    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        debugs(1, 0, "Running as " << WIN32_Service_name << " Windows System Service on " << WIN32_OS_string);
        debugs(1, 0, "Service command line is: " << WIN32_Service_Command_Line);
    } else
        debugs(1, 0, "Running on " << WIN32_OS_string);

#endif

    debugs(1, 1, "Process ID " << getpid());
    setSystemLimits();
    debugs(1, 1, "With " << Squid_MaxFD << " file descriptors available");

#ifdef _SQUID_MSWIN_

    debugs(1, 1, "With " << _getmaxstdio() << " CRT stdio descriptors available");

    if (WIN32_Socks_initialized)
        debugs(1, 1, "Windows sockets initialized");

    if (WIN32_OS_version > _WIN_OS_WINNT) {
        WIN32_IpAddrChangeMonitorInit();
    }

#endif

    if (!configured_once)
        disk_init();		/* disk_init must go before ipcache_init() */

    ipcache_init();

    fqdncache_init();

    parseEtcHosts();

#if USE_DNSSERVERS

    dnsInit();

#else

    idnsInit();

#endif

    redirectInit();

    authenticateInit(&Config.authConfiguration);

    externalAclInit();

    useragentOpenLog();

    refererOpenLog();

    httpHeaderInitModule();	/* must go before any header processing (e.g. the one in errorInitialize) */

    httpReplyInitModule();	/* must go before accepting replies */

    errorInitialize();

    accessLogInit();

#if ICAP_CLIENT
    icapLogOpen();
#endif

#if USE_IDENT
    Ident::Init();
#endif

#ifdef SQUID_SNMP

    snmpInit();

#endif
#if MALLOC_DBG

    malloc_debug(0, malloc_debug_level);

#endif

    if (!configured_once) {
#if USE_UNLINKD
        unlinkdInit();
#endif

        urlInitialize();
        statInit();
        storeInit();
        mainSetCwd();
        /* after this point we want to see the mallinfo() output */
        do_mallinfo = 1;
        mimeInit(Config.mimeTablePathname);
        refreshInit();
#if DELAY_POOLS

        DelayPools::Init();
#endif

        FwdState::initModule();
        /* register the modules in the cache manager menus */

        cbdataRegisterWithCacheManager();
        /* These use separate calls so that the comm loops can eventually
         * coexist.
         */

        eventInit();

        // TODO: pconn is a good candidate for new-style registration
        // PconnModule::GetInstance()->registerWithCacheManager();
        //   moved to PconnModule::PconnModule()
    }

#if USE_WCCP
    wccpInit();

#endif
#if USE_WCCPv2

    wccp2Init();

#endif

    serverConnectionsOpen();

    neighbors_init();

    // neighborsRegisterWithCacheManager(); //moved to neighbors_init()

    if (Config.chroot_dir)
        no_suid();

    if (!configured_once)
        writePidFile();		/* write PID file */

#ifdef _SQUID_LINUX_THREADS_

    squid_signal(SIGQUIT, rotate_logs, SA_RESTART);

    squid_signal(SIGTRAP, sigusr2_handle, SA_RESTART);

#else

    squid_signal(SIGUSR1, rotate_logs, SA_RESTART);

    squid_signal(SIGUSR2, sigusr2_handle, SA_RESTART);

#endif

    squid_signal(SIGHUP, reconfigure, SA_RESTART);

    squid_signal(SIGTERM, shut_down, SA_NODEFER | SA_RESETHAND | SA_RESTART);

    squid_signal(SIGINT, shut_down, SA_NODEFER | SA_RESETHAND | SA_RESTART);

#ifdef SIGTTIN

    squid_signal(SIGTTIN, shut_down, SA_NODEFER | SA_RESETHAND | SA_RESTART);

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

    debugs(1, 1, "Ready to serve requests.");

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