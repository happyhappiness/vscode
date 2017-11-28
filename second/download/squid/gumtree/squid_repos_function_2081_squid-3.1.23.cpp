static void
storeDigestRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("store_digest", "Store Digest", storeDigestReport, 0, 1);
}