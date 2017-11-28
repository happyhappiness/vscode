static void
httpHeaderRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("http_headers",
                        "HTTP Header Statistics",
                        httpHeaderStoreReport, 0, 1);
}