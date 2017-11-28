void
statFreeMemory(void)
{
    int i;

    for (i = 0; i < N_COUNT_HIST; ++i)
        statCountersClean(&CountHist[i]);

    for (i = 0; i < N_COUNT_HOUR_HIST; ++i)
        statCountersClean(&CountHourHist[i]);
}