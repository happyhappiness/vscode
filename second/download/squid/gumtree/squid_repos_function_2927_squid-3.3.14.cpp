static void
clientdbRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("client_list", "Cache Client List", clientdbDump, 0, 1);
}