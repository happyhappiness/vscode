int
SquidMain(int argc, char **argv)
{
    ConfigureCurrentKid(argv[0]);

    Debug::parseOptions(NULL);
    debug_log = stderr;

#if defined(SQUID_MAXFD_LIMIT)

    if (SQUID_MAXFD_LIMIT < Squid_MaxFD)
        Squid_MaxFD = SQUID_MAXFD_LIMIT;

#endif

    /* NOP under non-windows */
    int WIN32_init_err=0;
    if ((WIN32_init_err = WIN32_Subsystem_Init(&argc, &argv)))
        return WIN32_init_err;

    /* call mallopt() before anything else */
#if HAVE_MALLOPT
#ifdef M_GRAIN
    /* Round up all sizes to a multiple of this */
    mallopt(M_GRAIN, 16);

#endif
#ifdef M_MXFAST
    /* biggest size that is considered a small block */
    mallopt(M_MXFAST, 256);

#endif
#ifdef M_NBLKS
    /* allocate this many small blocks at once */
    mallopt(M_NLBLKS, 32);

#endif
#endif /* HAVE_MALLOPT */

    squid_srandom(time(NULL));

    getCurrentTime();

    squid_start = current_time;

    failure_notify = fatal_dump;

#if USE_WIN32_SERVICE

    WIN32_svcstatusupdate(SERVICE_START_PENDING, 10000);

#endif

    mainParseOptions(argc, argv);

    if (opt_parse_cfg_only) {
        Debug::parseOptions("ALL,1");
    }

#if USE_WIN32_SERVICE

    if (opt_install_service) {
        WIN32_InstallService();
        return 0;
    }

    if (opt_remove_service) {
        WIN32_RemoveService();
        return 0;
    }

    if (opt_command_line) {
        WIN32_SetServiceCommandLine();
        return 0;
    }

#endif

    /* parse configuration file
     * note: in "normal" case this used to be called from mainInitialize() */
    {
        int parse_err;

        if (!ConfigFile)
            ConfigFile = xstrdup(DefaultConfigFile);

        assert(!configured_once);

        Mem::Init();

        storeFsInit();      /* required for config parsing */

        /* TODO: call the FS::Clean() in shutdown to do Fs cleanups */
        Fs::Init();

        /* May not be needed for parsing, have not audited for such */
        DiskIOModule::SetupAllModules();

        /* Shouldn't be needed for config parsing, but have not audited for such */
        StoreFileSystem::SetupAllFs();

        /* we may want the parsing process to set this up in the future */
        Store::Root(new StoreController);
        Auth::Init();      /* required for config parsing. NOP if !USE_AUTH */
        Ip::ProbeTransport(); // determine IPv4 or IPv6 capabilities before parsing.

        Format::Token::Init(); // XXX: temporary. Use a runners registry of pre-parse runners instead.

        try {
            do_reconfigure = 0; // ignore any early (boot/startup) reconfigure signals
            parse_err = parseConfigFile(ConfigFile);
        } catch (...) {
            // for now any errors are a fatal condition...
            debugs(1, DBG_CRITICAL, "FATAL: Unhandled exception parsing config file." <<
                   (opt_parse_cfg_only ? " Run squid -k parse and check for errors." : ""));
            parse_err = 1;
        }

        Mem::Report();

        if (opt_parse_cfg_only || parse_err > 0)
            return parse_err;
    }
    setUmask(Config.umask);
    if (-1 == opt_send_signal)
        if (checkRunningPid())
            exit(0);

#if TEST_ACCESS

    comm_init();

    mainInitialize();

    test_access();

    return 0;

#endif

    /* send signal to running copy and exit */
    if (opt_send_signal != -1) {
        /* chroot if configured to run inside chroot */
        mainSetCwd();
        if (Config.chroot_dir) {
            no_suid();
        } else {
            leave_suid();
        }

        sendSignal();
        /* NOTREACHED */
    }

    debugs(1,2, HERE << "Doing post-config initialization\n");
    leave_suid();
    RunRegisteredHere(RegisteredRunner::finalizeConfig);
    RunRegisteredHere(RegisteredRunner::claimMemoryNeeds);
    RunRegisteredHere(RegisteredRunner::useConfig);
    enter_suid();

    if (!opt_no_daemon && Config.workers > 0)
        watch_child(argv);

    if (opt_create_swap_dirs) {
        /* chroot if configured to run inside chroot */
        mainSetCwd();

        setEffectiveUser();
        debugs(0, DBG_CRITICAL, "Creating missing swap directories");
        Store::Root().create();

        return 0;
    }

    if (IamPrimaryProcess())
        CpuAffinityCheck();
    CpuAffinityInit();

    setMaxFD();

    /* init comm module */
    comm_init();

    if (opt_no_daemon) {
        /* we have to init fdstat here. */
        fd_open(0, FD_LOG, "stdin");
        fd_open(1, FD_LOG, "stdout");
        fd_open(2, FD_LOG, "stderr");
    }

#if USE_WIN32_SERVICE

    WIN32_svcstatusupdate(SERVICE_START_PENDING, 10000);

#endif

    mainInitialize();

#if USE_WIN32_SERVICE

    WIN32_svcstatusupdate(SERVICE_RUNNING, 0);

#endif

    /* main loop */
    EventLoop mainLoop;

    SignalEngine signalEngine;

    mainLoop.registerEngine(&signalEngine);

    /* TODO: stop requiring the singleton here */
    mainLoop.registerEngine(EventScheduler::GetInstance());

    StoreRootEngine store_engine;

    mainLoop.registerEngine(&store_engine);

    CommSelectEngine comm_engine;

    mainLoop.registerEngine(&comm_engine);

    mainLoop.setPrimaryEngine(&comm_engine);

    /* use the standard time service */
    TimeEngine time_engine;

    mainLoop.setTimeService(&time_engine);

    if (IamCoordinatorProcess())
        AsyncJob::Start(Ipc::Coordinator::Instance());
    else if (UsingSmp() && (IamWorkerProcess() || IamDiskProcess()))
        AsyncJob::Start(new Ipc::Strand);

    /* at this point we are finished the synchronous startup. */
    starting_up = 0;

    mainLoop.run();

    if (mainLoop.errcount == 10)
        fatal_dump("Event loop exited with failure.");

    /* shutdown squid now */
    SquidShutdown();

    /* NOTREACHED */
    return 0;
}