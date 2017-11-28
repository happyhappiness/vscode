static void
storeDigestRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("store_digest", "Store Digest", storeDigestReport, 0, 1);
}