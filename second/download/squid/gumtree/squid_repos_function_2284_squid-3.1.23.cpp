static void
redirectRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("redirector", "URL Redirector Stats", redirectStats, 0, 1);
}