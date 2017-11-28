static void
fvdbRegisterWithCacheManager(void)
{
    Mgr::RegisterAction("via_headers", "Via Request Headers", fvdbDumpVia, 0, 1);
    Mgr::RegisterAction("forw_headers", "X-Forwarded-For Request Headers",
                        fvdbDumpForw, 0, 1);
}