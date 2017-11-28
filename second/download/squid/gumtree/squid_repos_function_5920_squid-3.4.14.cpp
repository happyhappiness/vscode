void
Icmp6::Recv(void)
{
    int n;
    struct addrinfo *from = NULL;
//    struct ip6_hdr *ip = NULL;
    static char *pkt = NULL;
    struct icmp6_hdr *icmp6header = NULL;
    icmpEchoData *echo = NULL;
    struct timeval now;
    static pingerReplyData preply;

    if (icmp_sock < 0) {
        debugs(42, DBG_CRITICAL, HERE << "dropping ICMPv6 read. No socket!?");
        return;
    }

    if (pkt == NULL) {
        pkt = (char *)xmalloc(MAX_PKT6_SZ);
    }

    Ip::Address::InitAddrInfo(from);

    n = recvfrom(icmp_sock,
                 (void *)pkt,
                 MAX_PKT6_SZ,
                 0,
                 from->ai_addr,
                 &from->ai_addrlen);

    if (n <= 0) {
        debugs(42, DBG_CRITICAL, HERE << "Error when calling recvfrom() on ICMPv6 socket.");
        Ip::Address::FreeAddrInfo(from);
        return;
    }

    preply.from = *from;

#if GETTIMEOFDAY_NO_TZP

    gettimeofday(&now);

#else

    gettimeofday(&now, NULL);

#endif

    debugs(42, 8, HERE << n << " bytes from " << preply.from);

// FIXME INET6 : The IPv6 Header (ip6_hdr) is not availble directly >:-(
//
// TTL still has to come from the IP header somewhere.
//	still need to strip and process it properly.
//	probably have to rely on RTT as given by timestamp in data sent and current.
    /* IPv6 Header Structures (linux)
    struct ip6_hdr

    // fields (via simple define)
    #define ip6_vfc		// N.A
    #define ip6_flow	// N/A
    #define ip6_plen	// payload length.
    #define ip6_nxt		// expect to be type 0x3a - ICMPv6
    #define ip6_hlim	// MAX hops  (always 64, but no guarantee)
    #define ip6_hops	// HOPS!!!  (can it be true??)

        ip = (struct ip6_hdr *) pkt;
        pkt += sizeof(ip6_hdr);

    debugs(42, DBG_CRITICAL, HERE << "ip6_nxt=" << ip->ip6_nxt <<
    		", ip6_plen=" << ip->ip6_plen <<
    		", ip6_hlim=" << ip->ip6_hlim <<
    		", ip6_hops=" << ip->ip6_hops	<<
    		" ::: 40 == sizef(ip6_hdr) == " << sizeof(ip6_hdr)
    );
    */

    icmp6header = (struct icmp6_hdr *) pkt;
    pkt += sizeof(icmp6_hdr);

    if (icmp6header->icmp6_type != ICMP6_ECHO_REPLY) {

        switch (icmp6header->icmp6_type) {
        case 134:
        case 135:
        case 136:
            /* ignore Router/Neighbour Advertisements */
            break;

        default:
            debugs(42, 8, HERE << preply.from << " said: " << icmp6header->icmp6_type << "/" << (int)icmp6header->icmp6_code << " " <<
                   IcmpPacketType(icmp6header->icmp6_type));
        }
        Ip::Address::FreeAddrInfo(from);
        return;
    }

    if (icmp6header->icmp6_id != icmp_ident) {
        debugs(42, 8, HERE << "dropping Icmp6 read. IDENT check failed. ident=='" << icmp_ident << "'=='" << icmp6header->icmp6_id << "'");
        Ip::Address::FreeAddrInfo(from);
        return;
    }

    echo = (icmpEchoData *) pkt;

    preply.opcode = echo->opcode;

    struct timeval tv;
    memcpy(&tv, &echo->tv, sizeof(struct timeval));
    preply.rtt = tvSubMsec(tv, now);

    /*
     * FIXME INET6: Without access to the IPv6-Hops header we must rely on the total RTT
     *      and could caculate the hops from that, but it produces some weird value mappings using ipHops
     *	for now everything is 1 v6 hop away with variant RTT
     * WANT:    preply.hops = ip->ip6_hops; // ipHops(ip->ip_hops);
     */
    preply.hops = 1;

    preply.psize = n - /* sizeof(ip6_hdr) - */ sizeof(icmp6_hdr) - (sizeof(icmpEchoData) - MAX_PKT6_SZ);

    /* Ensure the response packet has safe payload size */
    if ( preply.psize > (unsigned short) MAX_PKT6_SZ) {
        preply.psize = MAX_PKT6_SZ;
    } else if ( preply.psize < (unsigned short)0) {
        preply.psize = 0;
    }

    Log(preply.from,
        icmp6header->icmp6_type,
        IcmpPacketType(icmp6header->icmp6_type),
        preply.rtt,
        preply.hops);

    /* send results of the lookup back to squid.*/
    control.SendResult(preply, (sizeof(pingerReplyData) - PINGER_PAYLOAD_SZ + preply.psize) );
    Ip::Address::FreeAddrInfo(from);
}