static ssize_t
htcpBuildData(char *buf, size_t buflen, htcpStuff * stuff)
{
    ssize_t off = 0;
    ssize_t op_data_sz;
    size_t hdr_sz = sizeof(htcpDataHeader);

    if (buflen < hdr_sz)
        return -1;

    off += hdr_sz;      /* skip! */

    op_data_sz = htcpBuildOpData(buf + off, buflen - off, stuff);

    if (op_data_sz < 0)
        return op_data_sz;

    off += op_data_sz;

    debugs(31, 3, "htcpBuildData: hdr.length = " << off);

    if (!old_squid_format) {
        htcpDataHeader hdr;
        memset(&hdr, 0, sizeof(hdr));
        /* convert multi-byte fields */
        hdr.msg_id = htonl(stuff->msg_id);
        hdr.length = htons(static_cast<uint16_t>(off));
        hdr.opcode = stuff->op;
        hdr.response = stuff->response;
        hdr.RR = stuff->rr;
        hdr.F1 = stuff->f1;
        memcpy(buf, &hdr, hdr_sz);
    } else {
        htcpDataHeaderSquid hdrSquid;
        memset(&hdrSquid, 0, sizeof(hdrSquid));
        hdrSquid.length = htons(static_cast<uint16_t>(off));
        hdrSquid.opcode = stuff->op;
        hdrSquid.response = stuff->response;
        hdrSquid.F1 = stuff->f1;
        hdrSquid.RR = stuff->rr;
        memcpy(buf, &hdrSquid, hdr_sz);
    }

    debugs(31, 3, "htcpBuildData: size " << off);

    return off;
}