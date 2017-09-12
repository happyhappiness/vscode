void watchdogSignalHandler(int sig, siginfo_t *info, void *secret) {
    ucontext_t *uc = (ucontext_t*) secret;
    REDIS_NOTUSED(info);
    REDIS_NOTUSED(sig);
    sds st, log;

    log = sdsnew("\n--- WATCHDOG TIMER EXPIRED ---\n");
#ifdef HAVE_BACKTRACE
    st = getStackTrace(uc);
#else
    st = sdsnew("Sorry: no support for backtrace().\n");
#endif
    log = sdscatsds(log,st);
    log = sdscat(log,"------\n");
    redisLogFromHandler(REDIS_WARNING,log);
    sdsfree(st);
    sdsfree(log);
}