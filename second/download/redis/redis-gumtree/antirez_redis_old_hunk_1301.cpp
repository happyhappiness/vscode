    REDIS_NOTUSED(info);
    REDIS_NOTUSED(sig);

    redisLogFromHandler(REDIS_WARNING,"\n--- WATCHDOG TIMER EXPIRED ---");
#ifdef HAVE_BACKTRACE
    logStackTrace(uc);
#else
    redisLogFromHandler(REDIS_WARNING,"Sorry: no support for backtrace().");
#endif
    redisLogFromHandler(REDIS_WARNING,"--------\n");
}

/* Schedule a SIGALRM delivery after the specified period in milliseconds.
