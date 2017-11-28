void
refreshInit(void)
{
    memset(refreshCounts, 0, sizeof(refreshCounts));
    refreshCounts[rcHTTP].proto = "HTTP";
    refreshCounts[rcICP].proto = "ICP";
#if USE_HTCP

    refreshCounts[rcHTCP].proto = "HTCP";
#endif

    refreshCounts[rcStore].proto = "On Store";
#if USE_CACHE_DIGESTS

    refreshCounts[rcCDigest].proto = "Cache Digests";
#endif

    memset(&DefaultRefresh, '\0', sizeof(DefaultRefresh));
    DefaultRefresh.pattern = "<none>";
    DefaultRefresh.min = REFRESH_DEFAULT_MIN;
    DefaultRefresh.pct = REFRESH_DEFAULT_PCT;
    DefaultRefresh.max = REFRESH_DEFAULT_MAX;

    refreshRegisterWithCacheManager();
}