void
CacheDigest::add(const cache_key * key)
{
    assert(key);
    /* hash */
    cacheDigestHashKey(this, key);
    /* turn on corresponding bits */
#if CD_FAST_ADD

    CBIT_SET(mask, hashed_keys[0]);
    CBIT_SET(mask, hashed_keys[1]);
    CBIT_SET(mask, hashed_keys[2]);
    CBIT_SET(mask, hashed_keys[3]);
#else

    {
        int on_xition_cnt = 0;

        if (!CBIT_TEST(mask, hashed_keys[0])) {
            CBIT_SET(mask, hashed_keys[0]);
            ++on_xition_cnt;
        }

        if (!CBIT_TEST(mask, hashed_keys[1])) {
            CBIT_SET(mask, hashed_keys[1]);
            ++on_xition_cnt;
        }

        if (!CBIT_TEST(mask, hashed_keys[2])) {
            CBIT_SET(mask, hashed_keys[2]);
            ++on_xition_cnt;
        }

        if (!CBIT_TEST(mask, hashed_keys[3])) {
            CBIT_SET(mask, hashed_keys[3]);
            ++on_xition_cnt;
        }

        statCounter.cd.on_xition_count.count(on_xition_cnt);
    }
#endif
    ++count;
}