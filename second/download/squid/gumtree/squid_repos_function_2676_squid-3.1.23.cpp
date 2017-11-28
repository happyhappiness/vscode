static void

htcpHandleTstRequest(htcpDataHeader * dhdr, char *buf, int sz, IpAddress &from)
{
    /* buf should be a SPECIFIER */
    htcpSpecifier *s;

    if (sz == 0) {
        debugs(31, 3, "htcpHandleTst: nothing to do");
        return;
    }

    if (dhdr->F1 == 0)
        return;

    /* s is a new object */
    s = htcpUnpackSpecifier(buf, sz);

    s->setFrom(from);

    s->setDataHeader(dhdr);

    if (NULL == s) {
        debugs(31, 2, "htcpHandleTstRequest: htcpUnpackSpecifier failed");
        htcpLogHtcp(from, dhdr->opcode, LOG_UDP_INVALID, dash_str);
        return;
    }

    if (!s->request) {
        debugs(31, 2, "htcpHandleTstRequest: failed to parse request");
        htcpLogHtcp(from, dhdr->opcode, LOG_UDP_INVALID, dash_str);
        htcpFreeSpecifier(s);
        return;
    }

    if (!htcpAccessCheck(Config.accessList.htcp, s, from)) {
        debugs(31, 2, "htcpHandleTstRequest: Access denied");
        htcpLogHtcp(from, dhdr->opcode, LOG_UDP_DENIED, s->uri);
        htcpFreeSpecifier(s);
        return;
    }

    debugs(31, 3, "htcpHandleTstRequest: " << s->method << " " << s->uri << " " << s->version);
    debugs(31, 3, "htcpHandleTstRequest: " << s->req_hdrs);
    s->checkHit();
}