    ucontext_t *uc = (ucontext_t*) secret;
    sds infostring, clients;
    struct sigaction act;
    UNUSED(info);

    bugReportStart();
    serverLog(LL_WARNING,
        "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
    serverLog(LL_WARNING,
        "    Failed assertion: %s (%s:%d)", server.assert_failed,
                        server.assert_file, server.assert_line);

    /* Log the stack trace */
    serverLog(LL_WARNING, "--- STACK TRACE");
    logStackTrace(uc);

    /* Log INFO and CLIENT LIST */
    serverLog(LL_WARNING, "--- INFO OUTPUT");
    infostring = genRedisInfoString("all");
    infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
        dictGetHashFunctionSeed());
    serverLogRaw(LL_WARNING, infostring);
    serverLog(LL_WARNING, "--- CLIENT LIST OUTPUT");
    clients = getAllClientsInfoString();
    serverLogRaw(LL_WARNING, clients);
    sdsfree(infostring);
    sdsfree(clients);

