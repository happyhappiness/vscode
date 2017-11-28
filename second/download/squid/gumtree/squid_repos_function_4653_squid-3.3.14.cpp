static void
asnRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("asndb", "AS Number Database", asnStats, 0, 1);
}