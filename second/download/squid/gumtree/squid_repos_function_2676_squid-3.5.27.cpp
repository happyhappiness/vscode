static ssize_t
htcpBuildData(char *buf, size_t buflen, htcpStuff * stuff)
{
    ssize_t off = 0;
    ssize_t op_data_sz;
    size_t hdr_sz = sizeof(htcpDataHeader);
    htcpDataHeader hdr;

    if (buflen < hdr_sz)
        return -1;

    off += hdr_sz;      /* skip! */

    op_data_sz = htcpBuildOpData(buf + off, buflen - off, stuff);

    if (op_data_sz < 0)
        return op_data_sz;

    off += op_data_sz;

    debugs(31, 3, "htcpBuildData: hdr.length = " << off);

    hdr.length = (uint16_t) off;

    hdr.opcode = stuff->op;

    hdr.response = stuff->response;

    hdr.RR = stuff->rr;

    hdr.F1 = stuff->f1;

    hdr.msg_id = stuff->msg_id;

    /* convert multi-byte fields */
    hdr.length = htons(hdr.length);

    hdr.msg_id = htonl(hdr.msg_id);

    if (!old_squid_format) {
        memcpy(buf, &hdr, hdr_sz);
    } else {
        htcpDataHeaderSquid hdrSquid;
        memset(&hdrSquid, 0, sizeof(hdrSquid));
        hdrSquid.length = hdr.length;
        hdrSquid.opcode = hdr.opcode;
        hdrSquid.response = hdr.response;
        hdrSquid.F1 = hdr.F1;
        hdrSquid.RR = hdr.RR;
        memcpy(buf, &hdrSquid, hdr_sz);
    }

    debugs(31, 3, "htcpBuildData: size " << off);

    return off;
}