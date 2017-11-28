void
cbdataRegisterWithCacheManager(void)
{
    CacheManager *manager=CacheManager::GetInstance();
    manager->registerAction("cbdata",
                            "Callback Data Registry Contents",
                            cbdataDump, 0, 1);
#if CBDATA_DEBUG

    manager->registerAction("cbdatahistory",
                            "Detailed call history for all current cbdata contents",
                            cbdataDumpHistory, 0, 1);
#endif
}