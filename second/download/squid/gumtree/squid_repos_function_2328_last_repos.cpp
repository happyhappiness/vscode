CacheManager*
CacheManager::GetInstance()
{
    static CacheManager *instance = nullptr;
    if (!instance) {
        debugs(16, 6, "starting cachemanager up");
        instance = new CacheManager;
        Mgr::RegisterBasics();
    }
    return instance;
}