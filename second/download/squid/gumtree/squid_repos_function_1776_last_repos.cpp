void
storeDigestDel(const StoreEntry * entry)
{
#if USE_CACHE_DIGESTS

    if (!Config.onoff.digest_generation) {
        return;
    }

    assert(entry && store_digest);
    debugs(71, 6, "storeDigestDel: checking entry, key: " << entry->getMD5Text());

    if (!EBIT_TEST(entry->flags, KEY_PRIVATE)) {
        if (!store_digest->contains(static_cast<const cache_key *>(entry->key))) {
            ++sd_stats.del_lost_count;
            debugs(71, 6, "storeDigestDel: lost entry, key: " << entry->getMD5Text() << " url: " << entry->url()  );
        } else {
            ++sd_stats.del_count;
            store_digest->remove(static_cast<const cache_key *>(entry->key));
            debugs(71, 6, "storeDigestDel: deled entry, key: " << entry->getMD5Text());
        }
    }
#endif //USE_CACHE_DIGESTS
}