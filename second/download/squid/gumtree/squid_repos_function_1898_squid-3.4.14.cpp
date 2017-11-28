void
neighborsHtcpClear(StoreEntry * e, const char *uri, HttpRequest * req, const HttpRequestMethod &method, htcp_clr_reason reason)
{
    CachePeer *p;
    char buf[128];

    for (p = Config.peers; p; p = p->next) {
        if (!p->options.htcp) {
            continue;
        }
        if (p->options.htcp_no_clr) {
            continue;
        }
        if (p->options.htcp_no_purge_clr && reason == HTCP_CLR_PURGE) {
            continue;
        }
        debugs(15, 3, "neighborsHtcpClear: sending CLR to " << p->in_addr.toUrl(buf, 128));
        htcpClear(e, uri, req, method, p, reason);
    }
}