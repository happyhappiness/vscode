    storeAppendPrintf(sentry, "\nPeer Digests:\n");
    statPeerSelect(sentry);
    storeAppendPrintf(sentry, "\nLocal Digest:\n");
    storeDigestReport(sentry);
}

static double
statPctileSvc(double pctile, int interval, int which)
{
    StatCounters *f;
    StatCounters *l;
    double x;
