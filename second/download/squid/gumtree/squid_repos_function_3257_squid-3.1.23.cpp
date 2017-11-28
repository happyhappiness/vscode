void
snmpHandleUdp(int sock, void *not_used)
{
    LOCAL_ARRAY(char, buf, SNMP_REQUEST_SIZE);
    IpAddress from;
    snmp_request_t *snmp_rq;
    int len;

    debugs(49, 5, "snmpHandleUdp: Called.");

    commSetSelect(sock, COMM_SELECT_READ, snmpHandleUdp, NULL, 0);

    memset(buf, '\0', SNMP_REQUEST_SIZE);

    len = comm_udp_recvfrom(sock,
                            buf,
                            SNMP_REQUEST_SIZE,
                            0,
                            from);

    if (len > 0) {
        buf[len] = '\0';
        debugs(49, 3, "snmpHandleUdp: FD " << sock << ": received " << len << " bytes from " << from << ".");

        snmp_rq = (snmp_request_t *)xcalloc(1, sizeof(snmp_request_t));
        snmp_rq->buf = (u_char *) buf;
        snmp_rq->len = len;
        snmp_rq->sock = sock;
        snmp_rq->outbuf = (unsigned char *)xmalloc(snmp_rq->outlen = SNMP_REQUEST_SIZE);
        snmp_rq->from = from;
        snmpDecodePacket(snmp_rq);
        xfree(snmp_rq->outbuf);
        xfree(snmp_rq);
    } else {
        debugs(49, 1, "snmpHandleUdp: FD " << sock << " recvfrom: " << xstrerror());
    }
}