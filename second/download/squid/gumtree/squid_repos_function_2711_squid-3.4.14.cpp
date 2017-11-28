static void
htcpHandleMsg(char *buf, int sz, Ip::Address &from)
{
    htcpHeader htcpHdr;
    htcpDataHeader hdr;
    char *hbuf;
    int hsz;

    if (sz < 0 || (size_t)sz < sizeof(htcpHeader)) {
        // These are highly likely to be attack packets. Should probably get a bigger warning.
        debugs(31, 2, "htcpHandle: msg size less than htcpHeader size from " << from);
        return;
    }

    htcpHexdump("htcpHandle", buf, sz);
    memcpy(&htcpHdr, buf, sizeof(htcpHeader));
    htcpHdr.length = ntohs(htcpHdr.length);

    if (htcpHdr.minor == 0)
        old_squid_format = 1;
    else
        old_squid_format = 0;

    debugs(31, 3, "htcpHandle: htcpHdr.length = " << htcpHdr.length);
    debugs(31, 3, "htcpHandle: htcpHdr.major = " << htcpHdr.major);
    debugs(31, 3, "htcpHandle: htcpHdr.minor = " << htcpHdr.minor);

    if (sz != htcpHdr.length) {
        debugs(31, 3, "htcpHandle: sz/" << sz << " != htcpHdr.length/" <<
               htcpHdr.length << " from " << from );

        return;
    }

    if (htcpHdr.major != 0) {
        debugs(31, 3, "htcpHandle: Unknown major version " << htcpHdr.major << " from " << from );

        return;
    }

    hbuf = buf + sizeof(htcpHeader);
    hsz = sz - sizeof(htcpHeader);

    if ((size_t)hsz < sizeof(htcpDataHeader)) {
        debugs(31, 3, "htcpHandleData: msg size less than htcpDataHeader size");
        return;
    }

    if (!old_squid_format) {
        memcpy(&hdr, hbuf, sizeof(hdr));
    } else {
        htcpDataHeaderSquid hdrSquid;
        memcpy(&hdrSquid, hbuf, sizeof(hdrSquid));
        hdr.length = hdrSquid.length;
        hdr.opcode = hdrSquid.opcode;
        hdr.response = hdrSquid.response;
        hdr.F1 = hdrSquid.F1;
        hdr.RR = hdrSquid.RR;
        hdr.reserved = 0;
        hdr.msg_id = hdrSquid.msg_id;
    }

    hdr.length = ntohs(hdr.length);
    hdr.msg_id = ntohl(hdr.msg_id);
    debugs(31, 3, "htcpHandleData: hsz = " << hsz);
    debugs(31, 3, "htcpHandleData: length = " << hdr.length);

    if (hdr.opcode >= HTCP_END) {
        debugs(31, 3, "htcpHandleData: client " << from << ", opcode " << hdr.opcode << " out of range");
        return;
    }

    debugs(31, 3, "htcpHandleData: opcode = " << hdr.opcode << " " << htcpOpcodeStr[hdr.opcode]);
    debugs(31, 3, "htcpHandleData: response = " << hdr.response);
    debugs(31, 3, "htcpHandleData: F1 = " << hdr.F1);
    debugs(31, 3, "htcpHandleData: RR = " << hdr.RR);
    debugs(31, 3, "htcpHandleData: msg_id = " << hdr.msg_id);

    if (hsz < hdr.length) {
        debugs(31, 3, "htcpHandleData: sz < hdr.length");
        return;
    }

    /*
     * set sz = hdr.length so we ignore any AUTH fields following
     * the DATA.
     */
    hsz = (int) hdr.length;
    hbuf += sizeof(htcpDataHeader);
    hsz -= sizeof(htcpDataHeader);
    debugs(31, 3, "htcpHandleData: hsz = " << hsz);

    htcpHexdump("htcpHandleData", hbuf, hsz);

    switch (hdr.opcode) {
    case HTCP_NOP:
        htcpHandleNop(&hdr, hbuf, hsz, from);
        break;
    case HTCP_TST:
        htcpHandleTst(&hdr, hbuf, hsz, from);
        break;
    case HTCP_MON:
        htcpHandleMon(&hdr, hbuf, hsz, from);
        break;
    case HTCP_SET:
        htcpHandleSet(&hdr, hbuf, hsz, from);
        break;
    case HTCP_CLR:
        htcpHandleClr(&hdr, hbuf, hsz, from);
        htcpForwardClr(buf, sz);
        break;
    default:
        break;
    }
}