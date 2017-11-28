static void
refreshRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("refresh", "Refresh Algorithm Statistics", refreshStats, 0, 1);
}