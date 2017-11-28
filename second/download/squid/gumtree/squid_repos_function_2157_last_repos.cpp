static void
htcpHandleClr(htcpDataHeader * hdr, char *buf, int sz, Ip::Address &from)
{
    /* buf[0/1] is reserved and reason */
    int reason = buf[1] << 4;
    debugs(31, 2, "HTCP CLR reason: " << reason);
    buf += 2;
    sz -= 2;

    /* buf should be a SPECIFIER */

    if (sz == 0) {
        debugs(31, 4, "htcpHandleClr: nothing to do");
        htcpLogHtcp(from, hdr->opcode, LOG_UDP_INVALID, dash_str);
        return;
    }

    htcpSpecifier::Pointer s(htcpUnpackSpecifier(buf, sz));

    if (!s) {
        debugs(31, 3, "htcpHandleClr: htcpUnpackSpecifier failed");
        htcpLogHtcp(from, hdr->opcode, LOG_UDP_INVALID, dash_str);
        return;
    }

    if (!s->request) {
        debugs(31, 3, "htcpHandleTstRequest: failed to parse request");
        htcpLogHtcp(from, hdr->opcode, LOG_UDP_INVALID, dash_str);
        return;
    }

    if (!htcpAccessAllowed(Config.accessList.htcp_clr, s, from)) {
        debugs(31, 3, "htcpHandleClr: Access denied");
        htcpLogHtcp(from, hdr->opcode, LOG_UDP_DENIED, s->uri);
        return;
    }

    debugs(31, 2, "HTCP CLR request: " << s->method << " " << s->uri << " " << s->version);
    debugs(31, 2, "HTCP CLR headers: " << s->req_hdrs);

    /* Release objects from cache
     * analog to clientPurgeRequest in client_side.c
     */

    switch (htcpClrStore(s)) {

    case 1:
        htcpClrReply(hdr, 1, from); /* hit */
        htcpLogHtcp(from, hdr->opcode, LOG_UDP_HIT, s->uri);
        break;

    case 0:
        htcpClrReply(hdr, 0, from); /* miss */
        htcpLogHtcp(from, hdr->opcode, LOG_UDP_MISS, s->uri);
        break;

    default:
        break;
    }
}