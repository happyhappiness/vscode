static void
storeDigestAdd(const StoreEntry * entry)
{
    assert(entry && store_digest);

    if (storeDigestAddable(entry)) {
        ++sd_stats.add_count;

        if (store_digest->contains(static_cast<const cache_key *>(entry->key)))
            ++sd_stats.add_coll_count;

        store_digest->add(static_cast<const cache_key *>(entry->key));

        debugs(71, 6, "storeDigestAdd: added entry, key: " << entry->getMD5Text());
    } else {
        ++sd_stats.rej_count;

        if (store_digest->contains(static_cast<const cache_key *>(entry->key)))
            ++sd_stats.rej_coll_count;
    }
}