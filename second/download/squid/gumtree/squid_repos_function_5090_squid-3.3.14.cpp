static void commIncomingStats(StoreEntry *sentry)
{
    storeAppendPrintf(sentry, "Total number of devpoll loops: %ld\n", statCounter.select_loops);
    storeAppendPrintf(sentry, "Histogram of returned filedescriptors\n");
    statCounter.select_fds_hist.dump(sentry, statHistIntDumper);
}