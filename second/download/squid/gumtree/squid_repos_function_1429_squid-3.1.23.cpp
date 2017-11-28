static void
SquidShutdown()
{
    /* XXX: This function is called after the main loop has quit, which
     * means that no AsyncCalls would be called, including close handlers.
     * TODO: We need to close/shut/free everything that needs calls before
     * exiting the loop.
     */

#if USE_WIN32_SERVICE
    WIN32_svcstatusupdate(SERVICE_STOP_PENDING, 10000);
#endif

    debugs(1, 1, "Shutting down...");
#if USE_DNSSERVERS

    dnsShutdown();
#else

    idnsShutdown();
#endif
#if USE_SSL_CRTD
    Ssl::Helper::GetInstance()->Shutdown();
#endif
    redirectShutdown();
    externalAclShutdown();
    icpConnectionClose();
#if USE_HTCP

    htcpSocketClose();
#endif
#ifdef SQUID_SNMP

    snmpConnectionClose();
#endif
#if USE_WCCP

    wccpConnectionClose();
#endif
#if USE_WCCPv2

    wccp2ConnectionClose();
#endif

    releaseServerSockets();
    commCloseAllSockets();

#if USE_SQUID_ESI
    Esi::Clean();
#endif

#if DELAY_POOLS

    DelayPools::FreePools();
#endif

    authenticateShutdown();
#if USE_WIN32_SERVICE

    WIN32_svcstatusupdate(SERVICE_STOP_PENDING, 10000);
#endif

    Store::Root().sync(); /* Flush pending object writes/unlinks */
#if USE_UNLINKD

    unlinkdClose();	  /* after sync/flush */
#endif

    storeDirWriteCleanLogs(0);
    PrintRusage();
    dumpMallocStats();
    Store::Root().sync();		/* Flush log writes */
    storeLogClose();
    accessLogClose();
    useragentLogClose();
    refererCloseLog();
#if WIP_FWD_LOG

    fwdUninit();
#endif

    Store::Root().sync();		/* Flush log close */
    StoreFileSystem::FreeAllFs();
    DiskIOModule::FreeAllModules();
#if LEAK_CHECK_MODE && 0 /* doesn't work at the moment */

    configFreeMemory();
    storeFreeMemory();
    /*stmemFreeMemory(); */
    netdbFreeMemory();
    ipcacheFreeMemory();
    fqdncacheFreeMemory();
    asnFreeMemory();
    clientdbFreeMemory();
    httpHeaderCleanModule();
    statFreeMemory();
    eventFreeMemory();
    mimeFreeMemory();
    errorClean();
#endif
#if !XMALLOC_TRACE

    if (opt_no_daemon) {
        file_close(0);
        file_close(1);
        file_close(2);
    }

#endif
    // clear StoreController
    Store::Root(NULL);

    fdDumpOpen();

    comm_exit();

    memClean();

#if XMALLOC_TRACE

    xmalloc_find_leaks();

    debugs(1, 0, "Memory used after shutdown: " << xmalloc_total);

#endif
#if MEM_GEN_TRACE

    log_trace_done();

#endif

    if (Config.pidFilename && strcmp(Config.pidFilename, "none") != 0) {
        enter_suid();
        safeunlink(Config.pidFilename, 0);
        leave_suid();
    }

    debugs(1, 1, "Squid Cache (Version " << version_string << "): Exiting normally.");

    /*
     * DPW 2006-10-23
     * We used to fclose(debug_log) here if it was set, but then
     * we forgot to set it to NULL.  That caused some coredumps
     * because exit() ends up calling a bunch of destructors and
     * such.   So rather than forcing the debug_log to close, we'll
     * leave it open so that those destructors can write some
     * debugging if necessary.  The file will be closed anyway when
     * the process truly exits.
     */

    exit(shutdown_status);
}