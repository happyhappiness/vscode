static void
redirectRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("redirector", "URL Redirector Stats", redirectStats, 0, 1);
    Mgr::RegisterAction("store_id", "StoreId helper Stats", storeIdStats, 0, 1); /* registering the new StoreID statistics in Mgr*/
}