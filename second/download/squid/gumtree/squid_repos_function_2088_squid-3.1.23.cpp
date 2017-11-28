static void
storeDigestRebuildStart(void *datanotused)
{
    assert(store_digest);
    /* prevent overlapping if rebuild schedule is too tight */

    if (sd_state.rebuild_lock) {
        debugs(71, 1, "storeDigestRebuildStart: overlap detected, consider increasing rebuild period");
        return;
    }

    sd_state.rebuild_lock = 1;
    debugs(71, 2, "storeDigestRebuildStart: rebuild #" << sd_state.rebuild_count + 1);

    if (sd_state.rewrite_lock) {
        debugs(71, 2, "storeDigestRebuildStart: waiting for Rewrite to finish.");
        return;
    }

    storeDigestRebuildResume();
}