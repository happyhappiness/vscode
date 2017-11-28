void
refererOpenLog(void)
{
#if USE_REFERER_LOG
    assert(NULL == refererlog);

    if (!Config.Log.referer || (0 == strcmp(Config.Log.referer, "none"))) {
        debugs(40, 1, "Referer logging is disabled.");
        return;
    }

    refererlog = logfileOpen(Config.Log.referer, 0, 1);
#endif
}