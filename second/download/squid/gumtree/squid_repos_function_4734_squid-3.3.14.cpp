void
StoreFScoss::registerWithCacheManager()
{
    Mgr::RegisterAction("coss", "COSS Stats", Stats, 0, 1);
}