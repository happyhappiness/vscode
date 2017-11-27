static int
handle_udp(const struct udphdr *udp, int len,
	const struct in6_addr *s_addr,
	const struct in6_addr *d_addr)
{
    char buf[PCAP_SNAPLEN];
    if ((ntohs (udp->UDP_DEST) != 53)
		    && (ntohs (udp->UDP_SRC) != 53))
	return 0;
    memcpy(buf, udp + 1, len - sizeof(*udp));
    if (0 == handle_dns(buf, len - sizeof(*udp), s_addr, d_addr))
	return 0;
    return 1;
}