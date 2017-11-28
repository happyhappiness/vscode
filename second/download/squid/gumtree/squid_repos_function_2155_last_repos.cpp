static void
htcpHandleTstRequest(htcpDataHeader * dhdr, char *buf, int sz, Ip::Address &from)
{
    if (sz == 0) {
        debugs(31, 3, "htcpHandleTst: nothing to do");
        return;
    }

    if (dhdr->F1 == 0)
        return;

    /* buf should be a SPECIFIER */
    htcpSpecifier::Pointer s(htcpUnpackSpecifier(buf, sz));

    if (!s) {
        debugs(31, 3, "htcpHandleTstRequest: htcpUnpackSpecifier failed");
        htcpLogHtcp(from, dhdr->opcode, LOG_UDP_INVALID, dash_str);
        return;
    } else {
        s->setFrom(from);
        s->setDataHeader(dhdr);
    }

    if (!s->request) {
        debugs(31, 3, "htcpHandleTstRequest: failed to parse request");
        htcpLogHtcp(from, dhdr->opcode, LOG_UDP_INVALID, dash_str);
        return;
    }

    if (!htcpAccessAllowed(Config.accessList.htcp, s, from)) {
        debugs(31, 3, "htcpHandleTstRequest: Access denied");
        htcpLogHtcp(from, dhdr->opcode, LOG_UDP_DENIED, s->uri);
        return;
    }

    debugs(31, 2, "HTCP TST request: " << s->method << " " << s->uri << " " << s->version);
    debugs(31, 2, "HTCP TST headers: " << s->req_hdrs);
    s->checkHit();
}