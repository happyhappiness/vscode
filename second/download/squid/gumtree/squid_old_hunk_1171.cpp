    sum += refreshCountsStatsEntry(sentry, rc, STALE_FORCED_RELOAD, "Stale: request has no-cache directive");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_EXCEEDS_REQUEST_MAX_AGE_VALUE, "Stale: age exceeds request max-age value");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_EXPIRES, "Stale: expires time reached");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_MAX_RULE, "Stale: refresh_pattern max age rule");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_LMFACTOR_RULE, "Stale: refresh_pattern last-mod factor percentage");
    sum += refreshCountsStatsEntry(sentry, rc, STALE_DEFAULT, "Stale: by default");

    storeAppendPrintf(sentry, "%6d\t%6.2f\tTOTAL\n", rc.total, xpercent(rc.total, sum));
    storeAppendPrintf(sentry, "\n");
}

static void
refreshStats(StoreEntry * sentry)
{
    int i;
    int total = 0;

    /* get total usage count */

    for (i = 0; i < rcCount; ++i)
