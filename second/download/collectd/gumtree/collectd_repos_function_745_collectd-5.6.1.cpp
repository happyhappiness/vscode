static int
handle_ip(const struct ip *ip, int len)
{
    char buf[PCAP_SNAPLEN];
    int offset = ip->ip_hl << 2;
    struct in6_addr c_src_addr;
    struct in6_addr c_dst_addr;

    if (ip->ip_v == 6)
	return (handle_ipv6 ((void *) ip, len));

    in6_addr_from_buffer (&c_src_addr, &ip->ip_src.s_addr, sizeof (ip->ip_src.s_addr), AF_INET);
    in6_addr_from_buffer (&c_dst_addr, &ip->ip_dst.s_addr, sizeof (ip->ip_dst.s_addr), AF_INET);
    if (ignore_list_match (&c_src_addr))
	    return (0);
    if (IPPROTO_UDP != ip->ip_p)
	return 0;
    memcpy(buf, ((char *)ip) + offset, len - offset);
    if (0 == handle_udp((struct udphdr *) buf, len - offset))
	return 0;
    return 1;
}