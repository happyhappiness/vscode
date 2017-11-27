int ping_host_add (pingobj_t *obj, const char *host)
{
	pinghost_t *ph;

	struct sockaddr_storage sockaddr;
	socklen_t               sockaddr_len;

	struct addrinfo  ai_hints;
	struct addrinfo *ai_list, *ai_ptr;
	int              ai_return;

	dprintf ("host = %s\n", host);

	if (ping_host_search (obj->head, host) != NULL)
		return (0);

	memset (&ai_hints, '\0', sizeof (ai_hints));
	ai_hints.ai_flags     = 0;
#ifdef AI_ADDRCONFIG
	ai_hints.ai_flags    |= AI_ADDRCONFIG;
#endif
	ai_hints.ai_family    = obj->addrfamily;
	ai_hints.ai_socktype  = SOCK_RAW;

	if ((ph = ping_alloc ()) == NULL)
	{
		dprintf ("Out of memory!\n");
		return (-1);
	}

	if ((ph->hostname = strdup (host)) == NULL)
	{
		dprintf ("Out of memory!\n");
		ping_set_error (obj, "strdup", strerror (errno));
		ping_free (ph);
		return (-1);
	}

	/* obj->data is not garuanteed to be != NULL */
	if ((ph->data = strdup (obj->data == NULL ? PING_DEF_DATA : obj->data)) == NULL)
	{
		dprintf ("Out of memory!\n");
		ping_set_error (obj, "strdup", strerror (errno));
		ping_free (ph);
		return (-1);
	}

	if ((ai_return = getaddrinfo (host, NULL, &ai_hints, &ai_list)) != 0)
	{
		dprintf ("getaddrinfo failed\n");
		ping_set_error (obj, "getaddrinfo",
			       	(ai_return == EAI_SYSTEM)
				? strerror (errno)
				: gai_strerror (ai_return));
		ping_free (ph);
		return (-1);
	}

	if (ai_list == NULL)
		ping_set_error (obj, "getaddrinfo", "No hosts returned");

	for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		ph->fd = -1;

		sockaddr_len = sizeof (sockaddr);
		memset (&sockaddr, '\0', sockaddr_len);

		if (ai_ptr->ai_family == AF_INET)
		{
			struct sockaddr_in *si;

			si = (struct sockaddr_in *) &sockaddr;
			si->sin_family = AF_INET;
			si->sin_port   = htons (ph->ident);
			si->sin_addr.s_addr = htonl (INADDR_ANY);

			ai_ptr->ai_socktype = SOCK_RAW;
			ai_ptr->ai_protocol = IPPROTO_ICMP;
		}
		else if (ai_ptr->ai_family == AF_INET6)
		{
			struct sockaddr_in6 *si;

			si = (struct sockaddr_in6 *) &sockaddr;
			si->sin6_family = AF_INET6;
			si->sin6_port   = htons (ph->ident);
			si->sin6_addr   = in6addr_any;

			ai_ptr->ai_socktype = SOCK_RAW;
			ai_ptr->ai_protocol = IPPROTO_ICMPV6;
		}
		else
		{
			char errmsg[PING_ERRMSG_LEN];

			snprintf (errmsg, PING_ERRMSG_LEN, "Unknown `ai_family': %i", ai_ptr->ai_family);
			errmsg[PING_ERRMSG_LEN - 1] = '\0';

			dprintf (errmsg);
			ping_set_error (obj, "getaddrinfo", errmsg);
			continue;
		}

		/* TODO: Move this to a static function `ping_open_socket' and
		 * call it whenever the socket dies. */
		ph->fd = socket (ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
		if (ph->fd == -1)
		{
			dprintf ("socket: %s\n", strerror (errno));
			ping_set_error (obj, "socket", strerror (errno));
			continue;
		}

/*
 * The majority vote of operating systems has decided that you don't need to
 * bind here. This code should be reactivated to bind to a specific address,
 * though. See the `-I' option of `ping(1)' (GNU).  -octo
 */
#if 0
		if (bind (ph->fd, (struct sockaddr *) &sockaddr, sockaddr_len) == -1)
		{
			dprintf ("bind: %s\n", strerror (errno));
			ping_set_error (obj, "bind", strerror (errno));
			close (ph->fd);
			ph->fd = -1;
			continue;
		}
#endif

		assert (sizeof (struct sockaddr_storage) >= ai_ptr->ai_addrlen);
		memset (ph->addr, '\0', sizeof (struct sockaddr_storage));
		memcpy (ph->addr, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
		ph->addrlen = ai_ptr->ai_addrlen;
		ph->addrfamily = ai_ptr->ai_family;

		break;
	}

	freeaddrinfo (ai_list);

	if (ph->fd < 0)
	{
		free (ph->hostname);
		free (ph);
		return (-1);
	}

	/*
	 * Adding in the front is much easier, but then the iterator will
	 * return the host that was added last as first host. That's just not
	 * nice. -octo
	 */
	if (obj->head == NULL)
	{
		obj->head = ph;
	}
	else
	{
		pinghost_t *hptr;

		hptr = obj->head;
		while (hptr->next != NULL)
			hptr = hptr->next;

		assert ((hptr != NULL) && (hptr->next == NULL));
		hptr->next = ph;
	}

	ping_set_ttl (ph, obj->ttl);

	return (0);
}