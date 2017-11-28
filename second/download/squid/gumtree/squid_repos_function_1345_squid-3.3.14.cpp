bool
StoreMetaMD5::checkConsistency(StoreEntry *e) const
{
    assert (getType() == STORE_META_KEY_MD5);
    assert(length == SQUID_MD5_DIGEST_LENGTH);

    if (!EBIT_TEST(e->flags, KEY_PRIVATE) &&
            memcmp(value, e->key, SQUID_MD5_DIGEST_LENGTH)) {
        debugs(20, 2, "storeClientReadHeader: swapin MD5 mismatch");
        // debugs(20, 2, "\t" << storeKeyText((const cache_key *)value));
        debugs(20, 2, "\t" << e->getMD5Text());

        if (isPowTen(++md5_mismatches))
            debugs(20, DBG_IMPORTANT, "WARNING: " << md5_mismatches << " swapin MD5 mismatches");

        return false;
    }

    return true;
}