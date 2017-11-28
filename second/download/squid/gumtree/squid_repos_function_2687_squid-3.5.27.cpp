static void

htcpClrReply(htcpDataHeader * dhdr, int purgeSucceeded, Ip::Address &from)
{
    static char pkt[8192];
    ssize_t pktlen;

    /* If dhdr->F1 == 0, no response desired */

    if (dhdr->F1 == 0)
        return;

    htcpStuff stuff(dhdr->msg_id, HTCP_CLR, RR_RESPONSE, 0);

    stuff.response = purgeSucceeded ? 0 : 2;

    debugs(31, 3, "htcpClrReply: response = " << stuff.response);

    pktlen = htcpBuildPacket(pkt, sizeof(pkt), &stuff);

    if (pktlen == 0) {
        debugs(31, 3, "htcpClrReply: htcpBuildPacket() failed");
        return;
    }

    htcpSend(pkt, (int) pktlen, from);
}