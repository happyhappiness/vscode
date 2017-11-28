int
cacheDigestTest(const CacheDigest * cd, const cache_key * key)
{
    assert(cd && key);
    /* hash */
    cacheDigestHashKey(cd, key);
    /* test corresponding bits */
    return
        CBIT_TEST(cd->mask, hashed_keys[0]) &&
        CBIT_TEST(cd->mask, hashed_keys[1]) &&
        CBIT_TEST(cd->mask, hashed_keys[2]) &&
        CBIT_TEST(cd->mask, hashed_keys[3]);
}