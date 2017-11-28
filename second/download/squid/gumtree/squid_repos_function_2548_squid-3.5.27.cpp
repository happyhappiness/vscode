static void
ipcacheRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("ipcache",
                        "IP Cache Stats and Contents",
                        stat_ipcache_get, 0, 1);
}