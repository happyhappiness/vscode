    bioKillThreads();
    if (memtest_test_linux_anonymous_maps()) {
        serverLogRaw(LL_WARNING|LL_RAW,
            "!!! MEMORY ERROR DETECTED! Check your memory ASAP !!!");
    } else {
        serverLogRaw(LL_WARNING|LL_RAW,
            "Fast memory test PASSED, however your memory can still be broken. Please run a memory test for several hours if possible.");
    }
#endif

    serverLogRaw(LL_WARNING|LL_RAW,
"\n=== REDIS BUG REPORT END. Make sure to include from START to END. ===\n\n"
"       Please report the crash by opening an issue on github:\n\n"
"           http://github.com/antirez/redis/issues\n\n"
"  Suspect RAM error? Use redis-server --test-memory to verify it.\n\n"
);
    /* free(messages); Don't call free() with possibly corrupted memory. */
    if (server.daemonize && server.supervised == 0) unlink(server.pidfile);

    if (eip != NULL) {
        Dl_info info;
        if (dladdr(eip, &info) != 0)
        {
            serverLog(LL_WARNING,
                "symbol: %s (base %p), in module: %s (base: %p)",
                info.dli_sname, info.dli_saddr, info.dli_fname, info.dli_fbase);
            size_t len = (long)eip - (long)info.dli_saddr;
            long sz = sysconf(_SC_PAGESIZE);
            if (len < 1<<13) { /* we don't have functions over 8k (verified) */
                long end = ((long)eip + sz) & ~(sz-1); /* round up to page boundary */
                len = end - (long)info.dli_saddr;
                serverLogHexDump(LL_WARNING, "dump of function", info.dli_saddr ,len);
            }
        }
    }

    /* Make sure we exit with the right signal at the end. So for instance
     * the core will be dumped if enabled. */
    sigemptyset (&act.sa_mask);
