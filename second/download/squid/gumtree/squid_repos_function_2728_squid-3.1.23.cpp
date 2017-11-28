static void
httpHeaderRegisterWithCacheManager(void)
{
    CacheManager::GetInstance()->
    registerAction("http_headers",
                   "HTTP Header Statistics",
                   httpHeaderStoreReport, 0, 1);
}