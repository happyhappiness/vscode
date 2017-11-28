static void
storeLogRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("store_log_tags", "Histogram of store.log tags",
                        storeLogTagsHist, 0, 1);
}