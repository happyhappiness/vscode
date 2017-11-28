static void
netdbRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("netdb", "Network Measurement Database", netdbDump, 0, 1);
}