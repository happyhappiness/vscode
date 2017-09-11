    ucontext_t *uc = (ucontext_t*) secret;
    REDIS_NOTUSED(info);
    REDIS_NOTUSED(sig);

    /* Log INFO and CLIENT LIST */
    redisLog(REDIS_WARNING, "--- WATCHDOG TIMER EXPIRED ---"); 
#ifdef HAVE_BACKTRACE
    logStackTrace(uc);
    redisLog(REDIS_WARNING, "------");
#endif
}

/* Schedule a SIGALRM delivery after the specified period in milliseconds.
