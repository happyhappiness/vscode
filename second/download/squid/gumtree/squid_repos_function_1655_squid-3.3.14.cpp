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

    for (peer = getFirstPeer(); peer; peer = getNextPeer(peer)) {
        if (peer->digest)
            peerDigestStatsReport(peer->digest, sentry);
        else
            storeAppendPrintf(sentry, "\nNo peer digest from %s\n", peer->host);

        storeAppendPrintf(sentry, "\n");
    }

    storeAppendPrintf(sentry, "\nAlgorithm usage:\n");
    storeAppendPrintf(sentry, "Cache Digest: %7d (%3d%%)\n",
                      f->cd.times_used, xpercentInt(f->cd.times_used, tot_used));
    storeAppendPrintf(sentry, "Icp:          %7d (%3d%%)\n",
                      f->icp.times_used, xpercentInt(f->icp.times_used, tot_used));
    storeAppendPrintf(sentry, "Total:        %7d (%3d%%)\n",
                      tot_used, xpercentInt(tot_used, tot_used));
#else

    storeAppendPrintf(sentry, "peer digests are disabled; no stats is available.\n");
#endif
}