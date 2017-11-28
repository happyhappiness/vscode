void
PconnModule::registerWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("pconn",
                   "Persistent Connection Utilization Histograms",
                   DumpWrapper, 0, 1);
}