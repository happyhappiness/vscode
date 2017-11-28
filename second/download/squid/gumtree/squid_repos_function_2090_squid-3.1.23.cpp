static void
storeDigestRebuildFinish(void)
{
    assert(sd_state.rebuild_lock);
    sd_state.rebuild_lock = 0;
    sd_state.rebuild_count++;
    debugs(71, 2, "storeDigestRebuildFinish: done.");
    eventAdd("storeDigestRebuildStart", storeDigestRebuildStart, NULL, (double)
             Config.digest.rebuild_period, 1);
    /* resume pending Rewrite if any */

    if (sd_state.rewrite_lock)
        storeDigestRewriteResume();
}