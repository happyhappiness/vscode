static int
handle_ip(const struct ip *ip, int len)
{
    char buf[PCAP_SNAPLEN];
    int offset = ip->ip_hl << 2;
    struct in6_addr s_addr;
    struct in6_addr d_addr;

    if (ip->ip_v == 6)
	return (handle_ipv6 ((struct ip6_hdr *) ip, len));

    in6_addr_from_buffer (&s_addr, &ip->ip_src.s_addr, sizeof (ip->ip_src.s_addr), AF_INET);
    in6_addr_from_buffer (&d_addr, &ip->ip_dst.s_addr, sizeof (ip->ip_dst.s_addr), AF_INET);
    if (ignore_list_match (&s_addr))
	    return (0);
    if (IPPROTO_UDP != ip->ip_p)
	return 0;
    memcpy(buf, (void *) ip + offset, len - offset);
    if (0 == handle_udp((struct udphdr *) buf, len - offset, &s_addr, &d_addr))
	return 0;
    return 1;
}