        server.stat_numcommands,
        server.masterhost == NULL ? "master" : "slave"
    ));
    
    trace_size = backtrace(trace, 100);
    /* overwrite sigaction with caller's address */
    trace[1] = getMcontextEip(uc);
    messages = backtrace_symbols(trace, trace_size);

    for (i=0; i<trace_size; ++i) {
        char *fn = findFuncName(trace[i], &offset), *p;

        p = strchr(messages[i],'+');
        if (!fn || (p && ((unsigned long)strtol(p+1,NULL,10)) < offset)) {
            redisLog(REDIS_WARNING,"%s", messages[i]);
        } else {
            redisLog(REDIS_WARNING,"%d redis-server %p %s + %d", i, trace[i], fn, (unsigned int)offset);
        }
    }
    free(messages);
    exit(0);
}

static void setupSigSegvAction(void) {
    struct sigaction act;

    sigemptyset (&act.sa_mask);
    /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction
     * is used. Otherwise, sa_handler is used */
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND | SA_SIGINFO;
    act.sa_sigaction = segvHandler;
    sigaction (SIGSEGV, &act, NULL);
    sigaction (SIGBUS, &act, NULL);
}

/* =================================== Main! ================================ */

#ifdef __linux__
