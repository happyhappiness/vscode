void
Icmp6::SendEcho(Ip::Address &to, int opcode, const char *payload, int len)
{
    int x;
    LOCAL_ARRAY(char, pkt, MAX_PKT6_SZ);
    struct icmp6_hdr *icmp = NULL;
    icmpEchoData *echo = NULL;
    struct addrinfo *S = NULL;
    size_t icmp6_pktsize = 0;

    memset(pkt, '\0', MAX_PKT6_SZ);
    icmp = (struct icmp6_hdr *)pkt;

    /*
     * cevans - beware signed/unsigned issues in untrusted data from
     * the network!!
     */
    if (len < 0) {
        len = 0;
    }

    // Construct Icmp6 ECHO header
    icmp->icmp6_type = ICMP6_ECHO_REQUEST;
    icmp->icmp6_code = 0;
    icmp->icmp6_cksum = 0;
    icmp->icmp6_id = icmp_ident;
    icmp->icmp6_seq = (unsigned short) icmp_pkts_sent;
    ++icmp_pkts_sent;

    icmp6_pktsize = sizeof(struct icmp6_hdr);

    // Fill Icmp6 ECHO data content
    echo = (icmpEchoData *) (pkt + sizeof(icmp6_hdr));
    echo->opcode = (unsigned char) opcode;
    memcpy(&echo->tv, &current_time, sizeof(struct timeval));

    icmp6_pktsize += sizeof(struct timeval) + sizeof(char);

    if (payload) {
        if (len > MAX_PAYLOAD)
            len = MAX_PAYLOAD;

        memcpy(echo->payload, payload, len);

        icmp6_pktsize += len;
    }

    icmp->icmp6_cksum = CheckSum((unsigned short *) icmp, icmp6_pktsize);

    to.getAddrInfo(S);
    ((sockaddr_in6*)S->ai_addr)->sin6_port = 0;

    assert(icmp6_pktsize <= MAX_PKT6_SZ);

    debugs(42, 5, HERE << "Send Icmp6 packet to " << to << ".");

    x = sendto(icmp_sock,
               (const void *) pkt,
               icmp6_pktsize,
               0,
               S->ai_addr,
               S->ai_addrlen);

    if (x < 0) {
        debugs(42, DBG_IMPORTANT, HERE << "Error sending to ICMPv6 packet to " << to << ". ERR: " << xstrerror());
    }
    debugs(42,9, HERE << "x=" << x);

    Log(to, 0, NULL, 0, 0);
    Ip::Address::FreeAddr(S);
}