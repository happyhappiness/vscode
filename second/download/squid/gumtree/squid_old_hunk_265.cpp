    storeAppendPrintf(sentry, "\nPeer Digests:\n");
    statPeerSelect(sentry);
    storeAppendPrintf(sentry, "\nLocal Digest:\n");
    storeDigestReport(sentry);
}

static void
statAvg5min(StoreEntry * e)
{
    statAvgDump(e, 5, 0);
}

static void
statAvg60min(StoreEntry * e)
{
    statAvgDump(e, 60, 0);
}

static double
statPctileSvc(double pctile, int interval, int which)
{
    StatCounters *f;
    StatCounters *l;
    double x;
