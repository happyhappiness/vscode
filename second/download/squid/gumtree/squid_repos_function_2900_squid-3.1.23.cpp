static void
clientdbRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("client_list", "Cache Client List", clientdbDump, 0, 1);
}