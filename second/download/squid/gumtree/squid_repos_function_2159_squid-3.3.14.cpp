static void
storeDigestAdd(const StoreEntry * entry)
{
    assert(entry && store_digest);

    if (storeDigestAddable(entry)) {
        ++sd_stats.add_count;

        if (cacheDigestTest(store_digest, (const cache_key *)entry->key))
            ++sd_stats.add_coll_count;

        cacheDigestAdd(store_digest,  (const cache_key *)entry->key);

        debugs(71, 6, "storeDigestAdd: added entry, key: " << entry->getMD5Text());
    } else {
        ++sd_stats.rej_count;

        if (cacheDigestTest(store_digest,  (const cache_key *)entry->key))
            ++sd_stats.rej_coll_count;
    }
}