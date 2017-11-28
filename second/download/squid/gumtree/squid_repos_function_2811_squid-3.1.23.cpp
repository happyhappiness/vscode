CacheManager*
CacheManager::GetInstance()
{
    if (instance == 0) {
        debugs(16, 6, "CacheManager::GetInstance: starting cachemanager up");
        instance = new CacheManager;
    }
    return instance;
}