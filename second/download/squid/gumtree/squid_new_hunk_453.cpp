
static void
statPeerSelect(StoreEntry * sentry)
{
#if USE_CACHE_DIGESTS
    StatCounters *f = &statCounter;
    CachePeer *peer;
    const int tot_used = f->cd.times_used + f->icp.times_used;

    /* totals */
    cacheDigestGuessStatsReport(&f->cd.guess, sentry, "all peers");
    /* per-peer */
    storeAppendPrintf(sentry, "\nPer-peer statistics:\n");
