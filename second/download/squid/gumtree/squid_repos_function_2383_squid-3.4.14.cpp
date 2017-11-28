static void
idnsRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("idns", "Internal DNS Statistics", idnsStats, 0, 1);
}