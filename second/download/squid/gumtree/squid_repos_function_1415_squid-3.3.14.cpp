int
icpSetCacheKey(const cache_key * key)
{
    static int reqnum = 0;

    if (++reqnum < 0)
        reqnum = 1;

    storeKeyCopy(queried_keys[reqnum & N_QUERIED_KEYS_MASK], key);

    return reqnum;
}