void
storeFreeMemory(void)
{
    Store::FreeMemory();
#if USE_CACHE_DIGESTS
    delete store_digest;
#endif
    store_digest = NULL;
}