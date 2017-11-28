static void
accessLogRegisterWithCacheManager(void)
{
#if FORW_VIA_DB
    fvdbRegisterWithCacheManager();
#endif
}