static void
storeDigestSwapOutStep(void *data)
{
    StoreEntry *e = static_cast<StoreEntry *>(data);
    int chunk_size = Config.digest.swapout_chunk_size;
    assert(e == sd_state.rewrite_lock);
    assert(e);
    /* _add_ check that nothing bad happened while we were waiting @?@ @?@ */

    if (sd_state.rewrite_offset + chunk_size > store_digest->mask_size)
        chunk_size = store_digest->mask_size - sd_state.rewrite_offset;

    e->append(store_digest->mask + sd_state.rewrite_offset, chunk_size);

    debugs(71, 3, "storeDigestSwapOutStep: size: " << store_digest->mask_size <<
           " offset: " << sd_state.rewrite_offset << " chunk: " <<
           chunk_size << " bytes");

    sd_state.rewrite_offset += chunk_size;

    /* are we done ? */
    if (sd_state.rewrite_offset >= store_digest->mask_size)
        storeDigestRewriteFinish(e);
    else
        eventAdd("storeDigestSwapOutStep", storeDigestSwapOutStep, data, 0.0, 1, false);
}