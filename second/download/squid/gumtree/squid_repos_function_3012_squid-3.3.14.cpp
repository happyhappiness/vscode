static void
storeRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("storedir", "Store Directory Stats", Store::Stats, 0, 1);
    Mgr::RegisterAction("store_io", "Store IO Interface Stats", &Mgr::StoreIoAction::Create, 0, 1);
    Mgr::RegisterAction("store_check_cachable_stats", "storeCheckCachable() Stats",
                        storeCheckCachableStats, 0, 1);
}