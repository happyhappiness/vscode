static void
idnsRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("idns", "Internal DNS Statistics", idnsStats, 0, 1);
}