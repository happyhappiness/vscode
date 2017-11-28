static void
storeLogRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("store_log_tags", "Histogram of store.log tags",
                   storeLogTagsHist, 0, 1);
}