void
Ping::TimerStop(size_t fsize)
{
    if (!Ping::Config.enable)
        return;

    struct tm *tmp;
    time_t t2s;
    long elapsed_msec;

#if GETTIMEOFDAY_NO_TZP
    (void)gettimeofday(&tv2);
#else
    (void)gettimeofday(&tv2, NULL);
#endif

    elapsed_msec = tvSubMsec(tv1, tv2);
    t2s = tv2.tv_sec;
    tmp = localtime(&t2s);
    char tbuf[4096];
    snprintf(tbuf, sizeof(tbuf)-1, "%d-%02d-%02d %02d:%02d:%02d [%ld]: %ld.%03ld secs, %f KB/s",
             tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
             tmp->tm_hour, tmp->tm_min, tmp->tm_sec, stats.counted + 1,
             elapsed_msec / 1000, elapsed_msec % 1000,
             elapsed_msec ? (double) fsize / elapsed_msec : -1.0);
    std::cerr << tbuf << std::endl;

    if (!stats.counted || elapsed_msec < stats.pMin)
        stats.pMin = elapsed_msec;

    if (!stats.counted || elapsed_msec > stats.pMax)
        stats.pMax = elapsed_msec;

    stats.sum += elapsed_msec;

    ++stats.counted;

    /* Delay until next "ping.interval" boundary */
    if (!LoopDone(stats.counted) && elapsed_msec < Ping::Config.interval) {

        struct timeval tvs;
        long msec_left = Ping::Config.interval - elapsed_msec;

        tvs.tv_sec = msec_left / 1000;
        tvs.tv_usec = (msec_left % 1000) * 1000;
        select(0, NULL, NULL, NULL, &tvs);
    }
}