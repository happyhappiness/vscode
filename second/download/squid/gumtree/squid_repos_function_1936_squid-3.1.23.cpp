static void commIncomingStats(StoreEntry *sentry)
{
    StatCounters *f = &statCounter;
    storeAppendPrintf(sentry, "Total number of devpoll loops: %ld\n", statCounter.select_loops);
    storeAppendPrintf(sentry, "Histogram of returned filedescriptors\n");
    statHistDump(&f->select_fds_hist, sentry, statHistIntDumper);
}