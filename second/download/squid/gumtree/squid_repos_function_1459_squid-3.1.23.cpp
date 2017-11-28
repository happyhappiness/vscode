static void
carpRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("carp", "CARP information", carpCachemgr, 0, 1);
}