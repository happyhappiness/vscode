static void
storeDigestRebuildResume(void)
{
    assert(sd_state.rebuild_lock);
    assert(!sd_state.rewrite_lock);
    sd_state.theSearch = Store::Root().search();
    /* resize or clear */

    if (!storeDigestResize())
        store_digest->clear();     /* not clean()! */

    memset(&sd_stats, 0, sizeof(sd_stats));

    eventAdd("storeDigestRebuildStep", storeDigestRebuildStep, NULL, 0.0, 1);
}