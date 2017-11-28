void
statInit(void)
{
    int i;
    debugs(18, 5, "statInit: Initializing...");

    for (i = 0; i < N_COUNT_HIST; ++i)
        statCountersInit(&CountHist[i]);

    for (i = 0; i < N_COUNT_HOUR_HIST; ++i)
        statCountersInit(&CountHourHist[i]);

    statCountersInit(&statCounter);

    eventAdd("statAvgTick", statAvgTick, NULL, (double) COUNT_INTERVAL, 1);

    ClientActiveRequests.head = NULL;

    ClientActiveRequests.tail = NULL;

    statRegisterWithCacheManager();
}