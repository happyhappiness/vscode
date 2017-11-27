static int network_bind_socket (int fd, const struct addrinfo *ai)
{
	int loop = 0;
	int yes  = 1;

	/* allow multiple sockets to use the same PORT number */
	if (setsockopt (fd, SOL_SOCKET, SO_REUSEADDR,
				&yes, sizeof(yes)) == -1) {
                char errbuf[1024];
                ERROR ("setsockopt: %s", 
                                sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	DEBUG ("fd = %i; calling `bind'", fd);

	if (bind (fd, ai->ai_addr, ai->ai_addrlen) == -1)
	{
		char errbuf[1024];
		ERROR ("bind: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	if (ai->ai_family == AF_INET)
	{
		struct sockaddr_in *addr = (struct sockaddr_in *) ai->ai_addr;
		if (IN_MULTICAST (ntohl (addr->sin_addr.s_addr)))
		{
			struct ip_mreq mreq;

			DEBUG ("fd = %i; IPv4 multicast address found", fd);

			mreq.imr_multiaddr.s_addr = addr->sin_addr.s_addr;
			mreq.imr_interface.s_addr = htonl (INADDR_ANY);

			if (setsockopt (fd, IPPROTO_IP, IP_MULTICAST_LOOP,
						&loop, sizeof (loop)) == -1)
			{
				char errbuf[1024];
				ERROR ("setsockopt: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}

			if (setsockopt (fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
						&mreq, sizeof (mreq)) == -1)
			{
				char errbuf[1024];
				ERROR ("setsockopt: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}
		}
	}
	else if (ai->ai_family == AF_INET6)
	{
		/* Useful example: http://gsyc.escet.urjc.es/~eva/IPv6-web/examples/mcast.html */
		struct sockaddr_in6 *addr = (struct sockaddr_in6 *) ai->ai_addr;
		if (IN6_IS_ADDR_MULTICAST (&addr->sin6_addr))
		{
			struct ipv6_mreq mreq;

			DEBUG ("fd = %i; IPv6 multicast address found", fd);

			memcpy (&mreq.ipv6mr_multiaddr,
					&addr->sin6_addr,
					sizeof (addr->sin6_addr));

			/* http://developer.apple.com/documentation/Darwin/Reference/ManPages/man4/ip6.4.html
			 * ipv6mr_interface may be set to zeroes to
			 * choose the default multicast interface or to
			 * the index of a particular multicast-capable
			 * interface if the host is multihomed.
			 * Membership is associ-associated with a
			 * single interface; programs running on
			 * multihomed hosts may need to join the same
			 * group on more than one interface.*/
			mreq.ipv6mr_interface = 0;

			if (setsockopt (fd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP,
						&loop, sizeof (loop)) == -1)
			{
				char errbuf[1024];
				ERROR ("setsockopt: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}

			if (setsockopt (fd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
						&mreq, sizeof (mreq)) == -1)
			{
				char errbuf[1024];
				ERROR ("setsockopt: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}
		}
	}

	return (0);
}