void
useragentOpenLog(void)
{
#if USE_USERAGENT_LOG
    assert(NULL == useragentlog);

    if (!Config.Log.useragent || (0 == strcmp(Config.Log.useragent, "none"))) {
        debugs(40, 1, "User-Agent logging is disabled.");
        return;
    }

    useragentlog = logfileOpen(Config.Log.useragent, 0, 1);
#endif
}