static int
RFCNB_Set_Timeout(int seconds)
{
#ifdef SA_RESTART
    struct sigaction sa;
#endif
    int x;
    RFCNB_Timeout = seconds;
    if (RFCNB_Timeout <= 0)
        return 0;
#ifdef SA_RESTART
    sa.sa_handler = rfcnb_alarm;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    x = sigaction(SIGALRM, &sa, NULL);
    ;
#else
    signal(SIGALRM, rfcnb_alarm);
#endif
    if (x < 0) {
        syslog(LOG_ERR, "%s:%d: signal/sigaction: %s", __FILE__, __LINE__, strerror(errno));
        return -1;
    }
    return 0;
}