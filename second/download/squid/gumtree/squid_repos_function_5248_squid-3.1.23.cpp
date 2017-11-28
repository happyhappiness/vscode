void
Icmp4::Recv(void)
{
    int n;
    struct addrinfo *from = NULL;
    int iphdrlen = sizeof(iphdr);
    struct iphdr *ip = NULL;
    struct icmphdr *icmp = NULL;
    static char *pkt = NULL;
    struct timeval now;
    icmpEchoData *echo;
    static pingerReplyData preply;

    if (icmp_sock < 0) {
        debugs(42, 0, HERE << "No socket! Recv() should not be called.");
        return;
    }

    if (pkt == NULL)
        pkt = (char *)xmalloc(MAX_PKT4_SZ);

    preply.from.InitAddrInfo(from);
    n = recvfrom(icmp_sock,
                 (void *)pkt,
                 MAX_PKT4_SZ,
                 0,
                 from->ai_addr,
                 &from->ai_addrlen);

    preply.from = *from;

#if GETTIMEOFDAY_NO_TZP

    gettimeofday(&now);

#else

    gettimeofday(&now, NULL);

#endif

    debugs(42, 8, HERE << n << " bytes from " << preply.from);

    ip = (struct iphdr *) (void *) pkt;

#if HAVE_STRUCT_IPHDR_IP_HL

    iphdrlen = ip->ip_hl << 2;

#else /* HAVE_STRUCT_IPHDR_IP_HL */
#if WORDS_BIGENDIAN

    iphdrlen = (ip->ip_vhl >> 4) << 2;

#else

    iphdrlen = (ip->ip_vhl & 0xF) << 2;

#endif
#endif /* HAVE_STRUCT_IPHDR_IP_HL */

    icmp = (struct icmphdr *) (void *) (pkt + iphdrlen);

    if (icmp->icmp_type != ICMP_ECHOREPLY)
        return;

    if (icmp->icmp_id != icmp_ident)
        return;

    echo = (icmpEchoData *) (void *) (icmp + 1);

    preply.opcode = echo->opcode;

    preply.hops = ipHops(ip->ip_ttl);

    struct timeval tv;
    memcpy(&tv, &echo->tv, sizeof(struct timeval));
    preply.rtt = tvSubMsec(tv, now);

    preply.psize = n - iphdrlen - (sizeof(icmpEchoData) - MAX_PKT4_SZ);

    control.SendResult(preply, (sizeof(pingerReplyData) - MAX_PKT4_SZ + preply.psize) );

    Log(preply.from, icmp->icmp_type, icmpPktStr[icmp->icmp_type], preply.rtt, preply.hops);
}