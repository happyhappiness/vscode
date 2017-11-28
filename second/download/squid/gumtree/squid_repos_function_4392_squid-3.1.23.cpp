static void
asnRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->registerAction("asndb", "AS Number Database", asnStats, 0, 1);
}