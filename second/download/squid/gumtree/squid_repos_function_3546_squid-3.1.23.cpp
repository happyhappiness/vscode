static void
refreshStats(StoreEntry * sentry)
{
    int i;
    int total = 0;

    /* get total usage count */

    for (i = 0; i < rcCount; ++i)
        total += refreshCounts[i].total;

    /* protocol usage histogram */
    storeAppendPrintf(sentry, "\nRefreshCheck calls per protocol\n\n");

    storeAppendPrintf(sentry, "Protocol\t#Calls\t%%Calls\n");

    for (i = 0; i < rcCount; ++i)
        storeAppendPrintf(sentry, "%10s\t%6d\t%6.2f\n",
                          refreshCounts[i].proto,
                          refreshCounts[i].total,
                          xpercent(refreshCounts[i].total, total));

    /* per protocol histograms */
    storeAppendPrintf(sentry, "\n\nRefreshCheck histograms for various protocols\n");

    for (i = 0; i < rcCount; ++i)
        refreshCountsStats(sentry, &refreshCounts[i]);
}