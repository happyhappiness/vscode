static void in6_addr_from_buffer (struct in6_addr *ia,
	const void *buf, size_t buf_len,
	int family)
{
    memset (ia, 0, sizeof (struct in6_addr));
    if ((AF_INET == family) && (sizeof (uint32_t) == buf_len))
    {
	ia->s6_addr[10] = 0xFF;
	ia->s6_addr[11] = 0xFF;
	memcpy (ia->s6_addr + 12, buf, buf_len);
    }
    else if ((AF_INET6 == family) && (sizeof (struct in6_addr) == buf_len))
    {
	memcpy (ia, buf, buf_len);
    }
}