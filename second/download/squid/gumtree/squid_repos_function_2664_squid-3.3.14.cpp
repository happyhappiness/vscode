static void

htcpClrReply(htcpDataHeader * dhdr, int purgeSucceeded, Ip::Address &from)
{
    htcpStuff stuff;
    static char pkt[8192];
    ssize_t pktlen;

    /* If dhdr->F1 == 0, no response desired */

    if (dhdr->F1 == 0)
        return;

    memset(&stuff, '\0', sizeof(stuff));

    stuff.op = HTCP_CLR;

    stuff.rr = RR_RESPONSE;

    stuff.f1 = 0;

    stuff.response = purgeSucceeded ? 0 : 2;

    debugs(31, 3, "htcpClrReply: response = " << stuff.response);

    stuff.msg_id = dhdr->msg_id;

    pktlen = htcpBuildPacket(pkt, sizeof(pkt), &stuff);

    if (pktlen == 0) {
        debugs(31, 3, "htcpClrReply: htcpBuildPacket() failed");
        return;
    }

    htcpSend(pkt, (int) pktlen, from);
}