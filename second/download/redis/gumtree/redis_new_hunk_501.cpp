        start_addr = strtoul(start,NULL,16);
        end_addr = strtoul(end,NULL,16);
        size = end_addr-start_addr;

        start_vect[regions] = start_addr;
        size_vect[regions] = size;
        snprintf(logbuf,sizeof(logbuf),
            "*** Preparing to test memory region %lx (%lu bytes)\n",
                (unsigned long) start_vect[regions],
                (unsigned long) size_vect[regions]);
        if (write(fd,logbuf,strlen(logbuf)) == -1) { /* Nothing to do. */ }
        regions++;
    }

    int errors = 0;
    for (j = 0; j < regions; j++) {
        if (write(fd,".",1) == -1) { /* Nothing to do. */ }
        errors += memtest_preserving_test((void*)start_vect[j],size_vect[j],1);
        if (write(fd, errors ? "E" : "O",1) == -1) { /* Nothing to do. */ }
    }
    if (write(fd,"\n",1) == -1) { /* Nothing to do. */ }

    /* NOTE: It is very important to close the file descriptor only now
     * because closing it before may result into unmapping of some memory
     * region that we are testing. */
    fclose(fp);
    closeDirectLogFiledes(fd);
    return errors;
}
#endif

void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
    ucontext_t *uc = (ucontext_t*) secret;
    void *eip = getMcontextEip(uc);
    sds infostring, clients;
    struct sigaction act;
    UNUSED(info);

    bugReportStart();
    serverLog(LL_WARNING,
        "Redis %s crashed by signal: %d", REDIS_VERSION, sig);
    if (eip != NULL) {
        serverLog(LL_WARNING,
        "Crashed running the instuction at: %p", eip);
    }
    if (sig == SIGSEGV || sig == SIGBUS) {
        serverLog(LL_WARNING,
        "Accessing address: %p", (void*)info->si_addr);
    }
    serverLog(LL_WARNING,
        "Failed assertion: %s (%s:%d)", server.assert_failed,
                        server.assert_file, server.assert_line);

    /* Log the stack trace */
    serverLogRaw(LL_WARNING|LL_RAW, "\n------ STACK TRACE ------\n");
    logStackTrace(uc);

    /* Log INFO and CLIENT LIST */
    serverLogRaw(LL_WARNING|LL_RAW, "\n------ INFO OUTPUT ------\n");
    infostring = genRedisInfoString("all");
    infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
        dictGetHashFunctionSeed());
    serverLogRaw(LL_WARNING|LL_RAW, infostring);
    serverLogRaw(LL_WARNING|LL_RAW, "\n------ CLIENT LIST OUTPUT ------\n");
    clients = getAllClientsInfoString();
    serverLogRaw(LL_WARNING|LL_RAW, clients);
    sdsfree(infostring);
    sdsfree(clients);

    /* Log the current client */
    logCurrentClient();

    /* Log dump of processor registers */
    logRegisters(uc);

#if defined(HAVE_PROC_MAPS)
    /* Test memory */
    serverLogRaw(LL_WARNING|LL_RAW, "\n------ FAST MEMORY TEST ------\n");
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

    /* Make sure we exit with the right signal at the end. So for instance
     * the core will be dumped if enabled. */
    sigemptyset (&act.sa_mask);
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
    act.sa_handler = SIG_DFL;
