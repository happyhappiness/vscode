static int
storeDigestAddable(const StoreEntry * e)
{
    /* add some stats! XXX */

    debugs(71, 6, "storeDigestAddable: checking entry, key: " << e->getMD5Text());

    /* check various entry flags (mimics StoreEntry::checkCachable XXX) */

    if (EBIT_TEST(e->flags, KEY_PRIVATE)) {
        debugs(71, 6, "storeDigestAddable: NO: private key");
        return 0;
    }

    if (EBIT_TEST(e->flags, ENTRY_NEGCACHED)) {
        debugs(71, 6, "storeDigestAddable: NO: negative cached");
        return 0;
    }

    if (EBIT_TEST(e->flags, RELEASE_REQUEST)) {
        debugs(71, 6, "storeDigestAddable: NO: release requested");
        return 0;
    }

    if (e->store_status == STORE_OK && EBIT_TEST(e->flags, ENTRY_BAD_LENGTH)) {
        debugs(71, 6, "storeDigestAddable: NO: wrong content-length");
        return 0;
    }

    /* do not digest huge objects */
    if (e->swap_file_sz > (uint64_t )Config.Store.maxObjectSize) {
        debugs(71, 6, "storeDigestAddable: NO: too big");
        return 0;
    }

    /* still here? check staleness */
    /* Note: We should use the time of the next rebuild, not (cur_time+period) */
    if (refreshCheckDigest(e, Config.digest.rebuild_period)) {
        debugs(71, 6, "storeDigestAdd: entry expires within " << Config.digest.rebuild_period << " secs, ignoring");
        return 0;
    }

    /*
     * idea: how about also skipping very fresh (thus, potentially
     * unstable) entries? Should be configurable through
     * cd_refresh_pattern, of course.
     */
    /*
     * idea: skip objects that are going to be purged before the next
     * update.
     */
    return 1;
}