
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

