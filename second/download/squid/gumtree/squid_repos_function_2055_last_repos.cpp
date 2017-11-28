bool
CacheDigest::contains(const cache_key * key) const
{
    assert(key);
    /* hash */
    cacheDigestHashKey(this, key);
    /* test corresponding bits */
    return
        CBIT_TEST(mask, hashed_keys[0]) &&
        CBIT_TEST(mask, hashed_keys[1]) &&
        CBIT_TEST(mask, hashed_keys[2]) &&
        CBIT_TEST(mask, hashed_keys[3]);
}