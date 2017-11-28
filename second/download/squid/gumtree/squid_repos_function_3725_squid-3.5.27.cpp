static int
refreshCountsStatsEntry(StoreEntry * sentry, struct RefreshCounts &rc, int code, const char *desc)
{
    storeAppendPrintf(sentry, "%6d\t%6.2f\t%s\n", rc.status[code], xpercent(rc.status[code], rc.total), desc);
    return rc.status[code];
}