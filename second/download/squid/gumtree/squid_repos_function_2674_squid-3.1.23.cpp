static void

htcpHandleTst(htcpDataHeader * hdr, char *buf, int sz, IpAddress &from)
{
    debugs(31, 3, "htcpHandleTst: sz = " << sz);

    if (hdr->RR == RR_REQUEST)
        htcpHandleTstRequest(hdr, buf, sz, from);
    else
        htcpHandleTstResponse(hdr, buf, sz, from);
}