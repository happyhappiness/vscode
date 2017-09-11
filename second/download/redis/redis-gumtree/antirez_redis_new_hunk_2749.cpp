    /* Make sure we exit with the right signal at the end. So for instance
     * the core will be dumped if enabled. */
    sigemptyset (&act.sa_mask);
    act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
    act.sa_handler = SIG_DFL;
    sigaction (sig, &act, NULL);
    kill(getpid(),sig);
}
#endif /* HAVE_BACKTRACE */

/* =========================== Software Watchdog ============================ */
#include <sys/time.h>

void watchdogSignalHandler(int sig, siginfo_t *info, void *secret) {
    ucontext_t *uc = (ucontext_t*) secret;
    REDIS_NOTUSED(info);
    REDIS_NOTUSED(sig);
    sds st, log;
    time_t now = time(NULL);
    char date[128];
    FILE *fp;

    fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
    if (fp == NULL) return;

    strftime(date,sizeof(date),"%d %b %H:%M:%S",localtime(&now));
    log = sdscatprintf(sdsempty(),
        "\n--- WATCHDOG TIMER EXPIRED (%s) ---\n",date); 
#ifdef HAVE_BACKTRACE
    st = getStackTrace(uc);
#else
    st = sdsnew("Sorry: no support for backtrace().\n");
#endif
    log = sdscatsds(log,st);
    log = sdscat(log,"------\n\n");
    fprintf(fp,"%s",log);
    if (server.logfile) fclose(fp);
    sdsfree(st);
    sdsfree(log);
}

/* Schedule a SIGALRM delivery after the specified period in milliseconds.
 * If a timer is already scheduled, this function will re-schedule it to the
 * specified time. If period is 0 the current timer is disabled. */
void watchdogScheduleSignal(int period) {
    struct itimerval it;

    /* Will stop the timer if period is 0. */
    it.it_value.tv_sec = period/1000;
    it.it_value.tv_usec = (period%1000)*1000;
    /* Don't automatically restart. */
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &it, NULL);
}

/* Enable the software watchdong with the specified period in milliseconds. */
void enableWatchdog(int period) {
    if (server.watchdog_period == 0) {
        struct sigaction act;

        /* Watchdog was actually disabled, so we have to setup the signal
         * handler. */
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_SIGINFO;
        act.sa_sigaction = watchdogSignalHandler;
        sigaction(SIGALRM, &act, NULL);
    }
    if (period < 200) period = 200; /* We don't accept periods < 200 ms. */
    watchdogScheduleSignal(period); /* Adjust the current timer. */
    server.watchdog_period = period;
}

/* Disable the software watchdog. */
void disableWatchdog(void) {
    struct sigaction act;
    if (server.watchdog_period == 0) return; /* Already disabled. */
    watchdogScheduleSignal(0); /* Stop the current timer. */

    /* Set the signal handler to SIG_IGN, this will also remove pending
     * signals from the queue. */
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = SIG_IGN;
    sigaction(SIGALRM, &act, NULL);
    server.watchdog_period = 0;
}
