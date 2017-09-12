void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
    void *trace[100];
    char **messages = NULL;
    int i, trace_size = 0;
    ucontext_t *uc = (ucontext_t*) secret;
    sds infostring, clients;
    struct sigaction act;
    REDIS_NOTUSED(info);

    bugReportStart();
    redisLog(REDIS_WARNING,
        "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
    redisLog(REDIS_WARNING,
        "    Failed assertion: %s (%s:%d)", server.assert_failed,
                        server.assert_file, server.assert_line);

    /* Generate the stack trace */
    trace_size = backtrace(trace, 100);

    /* overwrite sigaction with caller's address */
    if (getMcontextEip(uc) != NULL) {
        trace[1] = getMcontextEip(uc);
    }
    messages = backtrace_symbols(trace, trace_size);
    redisLog(REDIS_WARNING, "--- STACK TRACE");
    for (i=1; i<trace_size; ++i)
        redisLog(REDIS_WARNING,"%s", messages[i]);

    /* Log INFO and CLIENT LIST */
    redisLog(REDIS_WARNING, "--- INFO OUTPUT");
    infostring = genRedisInfoString("all");
    infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
        dictGetHashFunctionSeed());
    redisLogRaw(REDIS_WARNING, infostring);
    redisLog(REDIS_WARNING, "--- CLIENT LIST OUTPUT");
    clients = getAllClientsInfoString();
    redisLogRaw(REDIS_WARNING, clients);
    /* Don't sdsfree() strings to avoid a crash. Memory may be corrupted. */

    /* Log CURRENT CLIENT info */
    if (server.current_client) {
        redisClient *cc = server.current_client;
        sds client;
        int j;

        redisLog(REDIS_WARNING, "--- CURRENT CLIENT INFO");
        client = getClientInfoString(cc);
        redisLog(REDIS_WARNING,"client: %s", client);
        /* Missing sdsfree(client) to avoid crash if memory is corrupted. */
        for (j = 0; j < cc->argc; j++) {
            robj *decoded;

            decoded = getDecodedObject(cc->argv[j]);
            redisLog(REDIS_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
            decrRefCount(decoded);
        }
        /* Check if the first argument, usually a key, is found inside the
         * selected DB, and if so print info about the associated object. */
        if (cc->argc >= 1) {
            robj *val, *key;
            dictEntry *de;

            key = getDecodedObject(cc->argv[1]);
            de = dictFind(cc->db->dict, key->ptr);
            if (de) {
                val = dictGetVal(de);
                redisLog(REDIS_WARNING,"key '%s' found in DB containing the following object:", key->ptr);
                redisLogObjectDebugInfo(val);
            }
            decrRefCount(key);
        }
    }

    /* Log dump of processor registers */
    logRegisters(uc);

    redisLog(REDIS_WARNING,
"\n=== REDIS BUG REPORT END. Make sure to include from START to END. ===\n\n"
"    Please report the crash opening an issue on github:\n\n"
"        http://github.com/antirez/redis/issues\n\n"
);
    /* free(messages); Don't call free() with possibly corrupted memory. */
    if (server.daemonize) unlink(server.pidfile);

    /* Make sure we exit with the right signal at the end. So for instance
     * the core will be dumped if enabled. */
    sigemptyset (&act.sa_mask);
    /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction
     * is used. Otherwise, sa_handler is used */
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
    act.sa_handler = SIG_DFL;
    sigaction (sig, &act, NULL);
    kill(getpid(),sig);
}