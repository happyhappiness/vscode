const cache_key *
icpGetCacheKey(const char *url, int reqnum)
{
    if (neighbors_do_private_keys && reqnum)
        return queried_keys[reqnum & N_QUERIED_KEYS_MASK];

    return storeKeyPublic(url, Http::METHOD_GET);
}