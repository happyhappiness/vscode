void
Icmp4::SendEcho(Ip::Address &to, int opcode, const char *payload, int len)
{
    int x;
    LOCAL_ARRAY(char, pkt, MAX_PKT4_SZ);

    struct icmphdr *icmp = NULL;
    icmpEchoData *echo;
    size_t icmp_pktsize = sizeof(struct icmphdr);
    struct addrinfo *S = NULL;

    memset(pkt, '\0', MAX_PKT4_SZ);

    icmp = (struct icmphdr *) (void *) pkt;

    /*
     * cevans - beware signed/unsigned issues in untrusted data from
     * the network!!
     */
    if (len < 0) {
        len = 0;
    }

    // Construct ICMP packet header
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_cksum = 0;
    icmp->icmp_id = icmp_ident;
    icmp->icmp_seq = (unsigned short) icmp_pkts_sent;
    ++icmp_pkts_sent;

    // Construct ICMP packet data content
    echo = (icmpEchoData *) (icmp + 1);
    echo->opcode = (unsigned char) opcode;
    memcpy(&echo->tv, &current_time, sizeof(struct timeval));

    icmp_pktsize += sizeof(struct timeval) + sizeof(char);

    if (payload) {
        if (len > MAX_PAYLOAD)
            len = MAX_PAYLOAD;

        memcpy(echo->payload, payload, len);

        icmp_pktsize += len;
    }

    icmp->icmp_cksum = CheckSum((unsigned short *) icmp, icmp_pktsize);

    to.getAddrInfo(S);
    ((sockaddr_in*)S->ai_addr)->sin_port = 0;
    assert(icmp_pktsize <= MAX_PKT4_SZ);

    debugs(42, 5, HERE << "Send ICMP packet to " << to << ".");

    x = sendto(icmp_sock,
               (const void *) pkt,
               icmp_pktsize,
               0,
               S->ai_addr,
               S->ai_addrlen);

    if (x < 0) {
        int xerrno = errno;
        debugs(42, DBG_IMPORTANT, MYNAME << "ERROR: sending to ICMP packet to " << to << ": " << xstrerr(xerrno));
    }

    Log(to, ' ', NULL, 0, 0);
    Ip::Address::FreeAddr(S);
}