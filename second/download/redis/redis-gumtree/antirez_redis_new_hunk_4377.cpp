    char **messages = NULL;
    int i, trace_size = 0;
    unsigned long offset=0;
    ucontext_t *uc = (ucontext_t*) secret;
    sds infostring;
    REDIS_NOTUSED(info);

    redisLog(REDIS_WARNING,
        "======= Ooops! Redis %s got signal: -%d- =======", REDIS_VERSION, sig);
    infostring = genRedisInfoString();
    redisLog(REDIS_WARNING, "%s",infostring);
    /* It's not safe to sdsfree() the returned string under memory
     * corruption conditions. Let it leak as we are going to abort */
    
    trace_size = backtrace(trace, 100);
    /* overwrite sigaction with caller's address */
