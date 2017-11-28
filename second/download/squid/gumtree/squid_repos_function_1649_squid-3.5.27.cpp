static void
carpRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("carp", "CARP information", carpCachemgr, 0, 1);
}