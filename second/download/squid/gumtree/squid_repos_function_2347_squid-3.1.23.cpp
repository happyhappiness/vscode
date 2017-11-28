void
ipcacheRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("ipcache",
                   "IP Cache Stats and Contents",
                   stat_ipcache_get, 0, 1);
}