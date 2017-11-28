static void
fqdncacheRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("fqdncache", "FQDN Cache Stats and Contents",
                        fqdnStats, 0, 1);

}