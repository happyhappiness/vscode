static void
storeDigestRebuildStep(void *datanotused)
{
    /* TODO: call Store::Root().size() to determine this.. */
    int count = Config.Store.objectsPerBucket * (int) ceil((double) store_hash_buckets *
                (double) Config.digest.rebuild_chunk_percentage / 100.0);
    assert(sd_state.rebuild_lock);

    debugs(71, 3, "storeDigestRebuildStep: buckets: " << store_hash_buckets << " entries to check: " << count);

    while (count-- && !sd_state.theSearch->isDone() && sd_state.theSearch->next())
        storeDigestAdd(sd_state.theSearch->currentItem());

    /* are we done ? */
    if (sd_state.theSearch->isDone())
        storeDigestRebuildFinish();
    else
        eventAdd("storeDigestRebuildStep", storeDigestRebuildStep, NULL, 0.0, 1);
}