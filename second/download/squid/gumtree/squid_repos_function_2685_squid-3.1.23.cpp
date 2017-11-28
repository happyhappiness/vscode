int
htcpQuery(StoreEntry * e, HttpRequest * req, peer * p)
{
    cache_key *save_key;
    static char pkt[8192];
    ssize_t pktlen;
    char vbuf[32];
    htcpStuff stuff;
    HttpHeader hdr(hoRequest);
    Packer pa;
    MemBuf mb;
    http_state_flags flags;

    if (htcpInSocket < 0)
        return 0;

    old_squid_format = p->options.htcp_oldsquid;
    memset(&flags, '\0', sizeof(flags));
    snprintf(vbuf, sizeof(vbuf), "%d/%d",
             req->http_ver.major, req->http_ver.minor);
    stuff.op = HTCP_TST;
    stuff.rr = RR_REQUEST;
    stuff.f1 = 1;
    stuff.response = 0;
    stuff.msg_id = ++msg_id_counter;
    stuff.S.method = (char *) RequestMethodStr(req->method);
    stuff.S.uri = (char *) e->url();
    stuff.S.version = vbuf;
    HttpStateData::httpBuildRequestHeader(req, req, e, &hdr, flags);
    mb.init();
    packerToMemInit(&pa, &mb);
    hdr.packInto(&pa);
    hdr.clean();
    packerClean(&pa);
    stuff.S.req_hdrs = mb.buf;
    pktlen = htcpBuildPacket(pkt, sizeof(pkt), &stuff);
    mb.clean();
    if (!pktlen) {
        debugs(31, 3, "htcpQuery: htcpBuildPacket() failed");
        return -1;
    }

    htcpSend(pkt, (int) pktlen, p->in_addr);

    queried_id[stuff.msg_id % N_QUERIED_KEYS] = stuff.msg_id;
    save_key = queried_keys[stuff.msg_id % N_QUERIED_KEYS];
    storeKeyCopy(save_key, (const cache_key *)e->key);
    queried_addr[stuff.msg_id % N_QUERIED_KEYS] = p->in_addr;
    debugs(31, 3, "htcpQuery: key (" << save_key << ") " << storeKeyText(save_key));

    return 1;
}