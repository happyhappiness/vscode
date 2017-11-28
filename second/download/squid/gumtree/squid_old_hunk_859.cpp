                          xpercent(refreshCounts[i].total, total));

    /* per protocol histograms */
    storeAppendPrintf(sentry, "\n\nRefreshCheck histograms for various protocols\n");

    for (i = 0; i < rcCount; ++i)
        refreshCountsStats(sentry, &refreshCounts[i]);
}

static void
refreshRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("refresh", "Refresh Algorithm Statistics", refreshStats, 0, 1);
