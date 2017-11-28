static void
htcpTstReply(htcpDataHeader * dhdr, StoreEntry * e, htcpSpecifier * spec, IpAddress &from)
{
    htcpStuff stuff;
    static char pkt[8192];
    HttpHeader hdr(hoHtcpReply);
    MemBuf mb;
    Packer p;
    ssize_t pktlen;
    memset(&stuff, '\0', sizeof(stuff));
    stuff.op = HTCP_TST;
    stuff.rr = RR_RESPONSE;
    stuff.f1 = 0;
    stuff.response = e ? 0 : 1;
    debugs(31, 3, "htcpTstReply: response = " << stuff.response);
    stuff.msg_id = dhdr->msg_id;

    if (spec) {
        mb.init();
        packerToMemInit(&p, &mb);
        stuff.S.method = spec->method;
        stuff.S.uri = spec->uri;
        stuff.S.version = spec->version;
        stuff.S.req_hdrs = spec->req_hdrs;
        if (e)
            hdr.putInt(HDR_AGE, (e->timestamp <= squid_curtime ? (squid_curtime - e->timestamp) : 0) );
        else
            hdr.putInt(HDR_AGE, 0);
        hdr.packInto(&p);
        stuff.D.resp_hdrs = xstrdup(mb.buf);
        debugs(31, 3, "htcpTstReply: resp_hdrs = {" << stuff.D.resp_hdrs << "}");
        mb.reset();
        hdr.reset();

        if (e && e->expires > -1)
            hdr.putTime(HDR_EXPIRES, e->expires);

        if (e && e->lastmod > -1)
            hdr.putTime(HDR_LAST_MODIFIED, e->lastmod);

        hdr.packInto(&p);

        stuff.D.entity_hdrs = xstrdup(mb.buf);

        debugs(31, 3, "htcpTstReply: entity_hdrs = {" << stuff.D.entity_hdrs << "}");

        mb.reset();

        hdr.reset();

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

        hdr.packInto(&p);
        stuff.D.cache_hdrs = xstrdup(mb.buf);
        debugs(31, 3, "htcpTstReply: cache_hdrs = {" << stuff.D.cache_hdrs << "}");
        mb.clean();
        hdr.clean();
        packerClean(&p);
    }

    pktlen = htcpBuildPacket(pkt, sizeof(pkt), &stuff);

    safe_free(stuff.D.resp_hdrs);
    safe_free(stuff.D.entity_hdrs);
    safe_free(stuff.D.cache_hdrs);

    if (!pktlen) {
        debugs(31, 3, "htcpTstReply: htcpBuildPacket() failed");
        return;
    }

    htcpSend(pkt, (int) pktlen, from);
}