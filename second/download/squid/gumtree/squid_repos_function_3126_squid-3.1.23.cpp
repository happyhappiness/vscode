void
fqdncacheRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("fqdncache", "FQDN Cache Stats and Contents",
                   fqdnStats, 0, 1);

}