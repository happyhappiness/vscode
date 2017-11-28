static void
fvdbRegisterWithCacheManager(void)
{
    CacheManager *manager=CacheManager::GetInstance();
    manager->registerAction("via_headers", "Via Request Headers", fvdbDumpVia, 0, 1);
    manager->registerAction("forw_headers", "X-Forwarded-For Request Headers",
                            fvdbDumpForw, 0, 1);
}