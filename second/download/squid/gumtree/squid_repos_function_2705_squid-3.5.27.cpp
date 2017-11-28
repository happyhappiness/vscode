int
htcpQuery(StoreEntry * e, HttpRequest * req, CachePeer * p)
{
    cache_key *save_key;
    static char pkt[8192];
    ssize_t pktlen;
    char vbuf[32];
    HttpHeader hdr(hoRequest);
    Packer pa;
    MemBuf mb;
    HttpStateFlags flags;

    if (!Comm::IsConnOpen(htcpIncomingConn))
        return 0;

    old_squid_format = p->options.htcp_oldsquid;
    memset(&flags, '\0', sizeof(flags));
    snprintf(vbuf, sizeof(vbuf), "%d/%d",
             req->http_ver.major, req->http_ver.minor);

    htcpStuff stuff(++msg_id_counter, HTCP_TST, RR_REQUEST, 1);
    SBuf sb = req->method.image();
    stuff.S.method = sb.c_str();
    stuff.S.uri = (char *) e->url();
    stuff.S.version = vbuf;
    HttpStateData::httpBuildRequestHeader(req, e, NULL, &hdr, flags);
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