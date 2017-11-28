void
purgeEntriesByUrl(HttpRequest * req, const char *url)
{
#if USE_HTCP
    bool get_or_head_sent = false;
#endif

    for (HttpRequestMethod m(METHOD_NONE); m != METHOD_ENUM_END; ++m) {
        if (m.isCacheble()) {
            if (StoreEntry *entry = storeGetPublic(url, m)) {
                debugs(88, 5, "purging " << RequestMethodStr(m) << ' ' << url);
#if USE_HTCP
                neighborsHtcpClear(entry, url, req, m, HTCP_CLR_INVALIDATION);
                if (m == METHOD_GET || m == METHOD_HEAD) {
                    get_or_head_sent = true;
                }
#endif
                entry->release();
            }
        }
    }

#if USE_HTCP
    if (!get_or_head_sent) {
        neighborsHtcpClear(NULL, url, req, HttpRequestMethod(METHOD_GET), HTCP_CLR_INVALIDATION);
    }
#endif
}