static void
statAvgTick(void *notused)
{
    StatCounters *t = &CountHist[0];
    StatCounters *p = &CountHist[1];
    StatCounters *c = &statCounter;

    struct rusage rusage;
    eventAdd("statAvgTick", statAvgTick, NULL, (double) COUNT_INTERVAL, 1);
    squid_getrusage(&rusage);
    c->page_faults = rusage_pagefaults(&rusage);
    c->cputime = rusage_cputime(&rusage);
    c->timestamp = current_time;
    /* even if NCountHist is small, we already Init()ed the tail */
    statCountersClean(CountHist + N_COUNT_HIST - 1);
    xmemmove(p, t, (N_COUNT_HIST - 1) * sizeof(StatCounters));
    statCountersCopy(t, c);
    NCountHist++;

    if ((NCountHist % COUNT_INTERVAL) == 0) {
        /* we have an hours worth of readings.  store previous hour */
        StatCounters *t2 = &CountHourHist[0];
        StatCounters *p2 = &CountHourHist[1];
        StatCounters *c2 = &CountHist[N_COUNT_HIST - 1];
        statCountersClean(CountHourHist + N_COUNT_HOUR_HIST - 1);
        xmemmove(p2, t2, (N_COUNT_HOUR_HIST - 1) * sizeof(StatCounters));
        statCountersCopy(t2, c2);
        NCountHourHist++;
    }

    if (Config.warnings.high_rptm > 0) {
        int i = (int) statPctileSvc(0.5, 20, PCTILE_HTTP);

        if (Config.warnings.high_rptm < i)
            debugs(18, 0, "WARNING: Median response time is " << i << " milliseconds");
    }

    if (Config.warnings.high_pf) {
        int i = (CountHist[0].page_faults - CountHist[1].page_faults);
        double dt = tvSubDsec(CountHist[0].timestamp, CountHist[1].timestamp);

        if (i > 0 && dt > 0.0) {
            i /= (int) dt;

            if (Config.warnings.high_pf < i)
                debugs(18, 0, "WARNING: Page faults occuring at " << i << "/sec");
        }
    }

    if (Config.warnings.high_memory) {
        size_t i = 0;
#if HAVE_MSTATS && HAVE_GNUMALLOC_H

        struct mstats ms = mstats();
        i = ms.bytes_total;
#elif HAVE_MALLINFO && HAVE_STRUCT_MALLINFO

        struct mallinfo mp = mallinfo();
        i = mp.arena;
#elif HAVE_SBRK

        i = (size_t) ((char *) sbrk(0) - (char *) sbrk_start);
#endif

        if (Config.warnings.high_memory < i)
            debugs(18, 0, "WARNING: Memory usage at " << ((unsigned long int)(i >> 20)) << " MB");
    }
}