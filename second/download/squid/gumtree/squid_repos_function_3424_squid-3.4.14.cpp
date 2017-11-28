void
purgeEntriesByUrl(HttpRequest * req, const char *url)
{
#if USE_HTCP
    bool get_or_head_sent = false;
#endif

    for (HttpRequestMethod m(Http::METHOD_NONE); m != Http::METHOD_ENUM_END; ++m) {
        if (m.respMaybeCacheable()) {
            if (StoreEntry *entry = storeGetPublic(url, m)) {
                debugs(88, 5, "purging " << RequestMethodStr(m) << ' ' << url);
#if USE_HTCP
                neighborsHtcpClear(entry, url, req, m, HTCP_CLR_INVALIDATION);
                if (m == Http::METHOD_GET || m == Http::METHOD_HEAD) {
                    get_or_head_sent = true;
                }
#endif
                entry->release();
            }
        }
    }

#if USE_HTCP
    if (!get_or_head_sent) {
        neighborsHtcpClear(NULL, url, req, HttpRequestMethod(Http::METHOD_GET), HTCP_CLR_INVALIDATION);
    }
#endif
}