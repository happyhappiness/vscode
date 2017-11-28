void
htcpClear(StoreEntry * e, const char *uri, HttpRequest * req, const HttpRequestMethod &, CachePeer * p, htcp_clr_reason reason)
{
    static char pkt[8192];
    ssize_t pktlen;
    char vbuf[32];
    HttpHeader hdr(hoRequest);
    MemBuf mb;
    Http::StateFlags flags;

    if (!Comm::IsConnOpen(htcpIncomingConn))
        return;

    old_squid_format = p->options.htcp_oldsquid;
    memset(&flags, '\0', sizeof(flags));
    snprintf(vbuf, sizeof(vbuf), "%d/%d",
             req->http_ver.major, req->http_ver.minor);

    htcpStuff stuff(++msg_id_counter, HTCP_CLR, RR_REQUEST, 0);
    if (reason == HTCP_CLR_INVALIDATION)
        stuff.reason = 1;

    SBuf sb = req->method.image();
    stuff.S.method = sb.c_str();
    if (e == NULL || e->mem_obj == NULL) {
        if (uri == NULL) {
            return;
        }
        stuff.S.uri = xstrdup(uri);
    } else {
        stuff.S.uri = (char *) e->url();
    }
    stuff.S.version = vbuf;
    if (reason != HTCP_CLR_INVALIDATION) {
        HttpStateData::httpBuildRequestHeader(req, e, NULL, &hdr, flags);
        mb.init();
        hdr.packInto(&mb);
        hdr.clean();
        stuff.S.req_hdrs = mb.buf;
    } else {
        stuff.S.req_hdrs = NULL;
    }
    pktlen = htcpBuildPacket(pkt, sizeof(pkt), &stuff);
    if (reason != HTCP_CLR_INVALIDATION) {
        mb.clean();
    }
    if (e == NULL) {
        xfree(stuff.S.uri);
    }
    if (!pktlen) {
        debugs(31, 3, "htcpClear: htcpBuildPacket() failed");
        return;
    }

    htcpSend(pkt, (int) pktlen, p->in_addr);
}