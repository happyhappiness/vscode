static int ping_set_ttl (pinghost_t *ph, int ttl)
{
	int ret = -2;

	if (ph->addrfamily == AF_INET)
	{
		ret = setsockopt (ph->fd, IPPROTO_IP, IP_TTL, &ttl, sizeof (ttl));
	}
	else if (ph->addrfamily == AF_INET6)
	{
		ret = setsockopt (ph->fd, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &ttl, sizeof (ttl));
	}

	return (ret);
}