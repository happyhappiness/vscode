static void
netdbRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("netdb", "Network Measurement Database", netdbDump, 0, 1);
}