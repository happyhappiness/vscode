void
storeDigestReport(StoreEntry * e)
{
#if USE_CACHE_DIGESTS

    if (!Config.onoff.digest_generation) {
        return;
    }

    if (store_digest) {
        cacheDigestReport(store_digest, "store", e);
        storeAppendPrintf(e, "\t added: %d rejected: %d ( %.2f %%) del-ed: %d\n",
                          sd_stats.add_count,
                          sd_stats.rej_count,
                          xpercent(sd_stats.rej_count, sd_stats.rej_count + sd_stats.add_count),
                          sd_stats.del_count);
        storeAppendPrintf(e, "\t collisions: on add: %.2f %% on rej: %.2f %%\n",
                          xpercent(sd_stats.add_coll_count, sd_stats.add_count),
                          xpercent(sd_stats.rej_coll_count, sd_stats.rej_count));
    } else {
        storeAppendPrintf(e, "store digest: disabled.\n");
    }

#endif
}