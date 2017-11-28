void
cbdataRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("cbdata",
                        "Callback Data Registry Contents",
                        cbdataDump, 0, 1);
#if USE_CBDATA_DEBUG

    Mgr::RegisterAction("cbdatahistory",
                        "Detailed call history for all current cbdata contents",
                        cbdataDumpHistory, 0, 1);
#endif
}