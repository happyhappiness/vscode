static void
accessLogRegisterWithCacheManager(void)
{
#if USE_FORW_VIA_DB
    fvdbRegisterWithCacheManager();
#endif
}