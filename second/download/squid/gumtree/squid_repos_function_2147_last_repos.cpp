static void
htcpTstReply(htcpDataHeader * dhdr, StoreEntry * e, htcpSpecifier * spec, Ip::Address &from)
{
    static char pkt[8192];
    HttpHeader hdr(hoHtcpReply);
    ssize_t pktlen;

    htcpStuff stuff(dhdr->msg_id, HTCP_TST, RR_RESPONSE, 0);
    stuff.response = e ? 0 : 1;
    debugs(31, 3, "htcpTstReply: response = " << stuff.response);

    if (spec) {
        stuff.S.method = spec->method;
        stuff.S.uri = spec->uri;
        stuff.S.version = spec->version;
        stuff.S.req_hdrs = spec->req_hdrs;
        stuff.S.reqHdrsSz = spec->reqHdrsSz;
        if (e)
            hdr.putInt(Http::HdrType::AGE, (e->timestamp <= squid_curtime ? (squid_curtime - e->timestamp) : 0) );
        else
            hdr.putInt(Http::HdrType::AGE, 0);
        MemBuf mb;
        mb.init();
        hdr.packInto(&mb);
        stuff.D.resp_hdrs = xstrdup(mb.buf);
        stuff.D.respHdrsSz = mb.contentSize();
        debugs(31, 3, "htcpTstReply: resp_hdrs = {" << stuff.D.resp_hdrs << "}");
        mb.reset();
        hdr.clean();

        if (e && e->expires > -1)
            hdr.putTime(Http::HdrType::EXPIRES, e->expires);

        if (e && e->lastModified() > -1)
            hdr.putTime(Http::HdrType::LAST_MODIFIED, e->lastModified());

        hdr.packInto(&mb);

        stuff.D.entity_hdrs = xstrdup(mb.buf);
        stuff.D.entityHdrsSz = mb.contentSize();

        debugs(31, 3, "htcpTstReply: entity_hdrs = {" << stuff.D.entity_hdrs << "}");

        mb.reset();
        hdr.clean();

#if USE_ICMP
        if (char *host = urlHostname(spec->uri)) {
            int rtt = 0;
            int hops = 0;
            int samp = 0;
            netdbHostData(host, &samp, &rtt, &hops);

            if (rtt || hops) {
                char cto_buf[128];
                snprintf(cto_buf, 128, "%s %d %f %d",
                         host, samp, 0.001 * rtt, hops);
                hdr.putExt("Cache-to-Origin", cto_buf);
            }
        }
#endif /* USE_ICMP */

        hdr.packInto(&mb);
        stuff.D.cache_hdrs = xstrdup(mb.buf);
        stuff.D.cacheHdrsSz = mb.contentSize();
        debugs(31, 3, "htcpTstReply: cache_hdrs = {" << stuff.D.cache_hdrs << "}");
        mb.clean();
        hdr.clean();
    }

    pktlen = htcpBuildPacket(pkt, sizeof(pkt), &stuff);

    safe_free(stuff.D.resp_hdrs);
    stuff.D.respHdrsSz = 0;
    safe_free(stuff.D.entity_hdrs);
    stuff.D.entityHdrsSz = 0;
    safe_free(stuff.D.cache_hdrs);
    stuff.D.cacheHdrsSz = 0;

    if (!pktlen) {
        debugs(31, 3, "htcpTstReply: htcpBuildPacket() failed");
        return;
    }

    htcpSend(pkt, (int) pktlen, from);
}