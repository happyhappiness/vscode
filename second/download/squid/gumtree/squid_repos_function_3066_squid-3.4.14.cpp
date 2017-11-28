void
storeFreeMemory(void)
{
    Store::Root(NULL);
#if USE_CACHE_DIGESTS

    if (store_digest)
        cacheDigestDestroy(store_digest);

#endif

    store_digest = NULL;
}