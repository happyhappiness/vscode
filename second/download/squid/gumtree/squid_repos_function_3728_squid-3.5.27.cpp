static void
refreshRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("refresh", "Refresh Algorithm Statistics", refreshStats, 0, 1);
}