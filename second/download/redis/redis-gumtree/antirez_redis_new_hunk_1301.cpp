    REDIS_NOTUSED(info);
    REDIS_NOTUSED(sig);

    serverLogFromHandler(REDIS_WARNING,"\n--- WATCHDOG TIMER EXPIRED ---");
#ifdef HAVE_BACKTRACE
    logStackTrace(uc);
#else
    serverLogFromHandler(REDIS_WARNING,"Sorry: no support for backtrace().");
#endif
    serverLogFromHandler(REDIS_WARNING,"--------\n");
}

/* Schedule a SIGALRM delivery after the specified period in milliseconds.
