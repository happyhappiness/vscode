static void
storeRegisterWithCacheManager(void)
{
    CacheManager *manager=CacheManager::GetInstance();
    manager->registerAction("storedir", "Store Directory Stats", Store::Stats, 0, 1);
    manager->registerAction("store_io", "Store IO Interface Stats", storeIOStats, 0, 1);
    manager->registerAction("store_check_cachable_stats", "storeCheckCachable() Stats",
                            storeCheckCachableStats, 0, 1);
}