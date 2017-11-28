void
htcpClear(StoreEntry * e, const char *uri, HttpRequest * req, const HttpRequestMethod &method, CachePeer * p, htcp_clr_reason reason)
{
    static char pkt[8192];
    ssize_t pktlen;
    char vbuf[32];
    htcpStuff stuff;
    HttpHeader hdr(hoRequest);
    Packer pa;
    MemBuf mb;
    HttpStateFlags flags;

    if (!Comm::IsConnOpen(htcpIncomingConn))
        return;

    old_squid_format = p->options.htcp_oldsquid;
    memset(&flags, '\0', sizeof(flags));
    snprintf(vbuf, sizeof(vbuf), "%d/%d",
             req->http_ver.major, req->http_ver.minor);
    stuff.op = HTCP_CLR;
    stuff.rr = RR_REQUEST;
    stuff.f1 = 0;
    stuff.response = 0;
    stuff.msg_id = ++msg_id_counter;
    switch (reason) {
    case HTCP_CLR_INVALIDATION:
        stuff.reason = 1;
        break;
    default:
        stuff.reason = 0;
        break;
    }
    stuff.S.method = (char *) RequestMethodStr(req->method);
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
        packerToMemInit(&pa, &mb);
        hdr.packInto(&pa);
        hdr.clean();
        packerClean(&pa);
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