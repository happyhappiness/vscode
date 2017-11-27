static int network_set_ttl (const sockent_t *se, const struct addrinfo *ai)
{
	if ((network_config_ttl < 1) || (network_config_ttl > 255))
		return (-1);

	DEBUG ("ttl = %i", network_config_ttl);

	if (ai->ai_family == AF_INET)
	{
		struct sockaddr_in *addr = (struct sockaddr_in *) ai->ai_addr;
		int optname;

		if (IN_MULTICAST (ntohl (addr->sin_addr.s_addr)))
			optname = IP_MULTICAST_TTL;
		else
			optname = IP_TTL;

		if (setsockopt (se->fd, IPPROTO_IP, optname,
					&network_config_ttl,
					sizeof (network_config_ttl)) == -1)
		{
			char errbuf[1024];
			ERROR ("setsockopt: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return (-1);
		}
	}
	else if (ai->ai_family == AF_INET6)
	{
		/* Useful example: http://gsyc.escet.urjc.es/~eva/IPv6-web/examples/mcast.html */
		struct sockaddr_in6 *addr = (struct sockaddr_in6 *) ai->ai_addr;
		int optname;

		if (IN6_IS_ADDR_MULTICAST (&addr->sin6_addr))
			optname = IPV6_MULTICAST_HOPS;
		else
			optname = IPV6_UNICAST_HOPS;

		if (setsockopt (se->fd, IPPROTO_IPV6, optname,
					&network_config_ttl,
					sizeof (network_config_ttl)) == -1)
		{
			char errbuf[1024];
			ERROR ("setsockopt: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}
	}

	return (0);
}