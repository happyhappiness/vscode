static sockent_t *network_create_socket (const char *node,
		const char *service,
		int listen)
{
	struct addrinfo  ai_hints;
	struct addrinfo *ai_list, *ai_ptr;
	int              ai_return;

	sockent_t *se_head = NULL;
	sockent_t *se_tail = NULL;

	DEBUG ("node = %s, service = %s", node, service);

	memset (&ai_hints, '\0', sizeof (ai_hints));
	ai_hints.ai_flags    = 0;
#ifdef AI_PASSIVE
	ai_hints.ai_flags |= AI_PASSIVE;
#endif
#ifdef AI_ADDRCONFIG
	ai_hints.ai_flags |= AI_ADDRCONFIG;
#endif
	ai_hints.ai_family   = AF_UNSPEC;
	ai_hints.ai_socktype = SOCK_DGRAM;
	ai_hints.ai_protocol = IPPROTO_UDP;

	ai_return = getaddrinfo (node, service, &ai_hints, &ai_list);
	if (ai_return != 0)
	{
		char errbuf[1024];
		ERROR ("getaddrinfo (%s, %s): %s",
				(node == NULL) ? "(null)" : node,
				(service == NULL) ? "(null)" : service,
				(ai_return == EAI_SYSTEM)
				? sstrerror (errno, errbuf, sizeof (errbuf))
				: gai_strerror (ai_return));
		return (NULL);
	}

	for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		sockent_t *se;

		if ((se = (sockent_t *) malloc (sizeof (sockent_t))) == NULL)
		{
			char errbuf[1024];
			ERROR ("malloc: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			continue;
		}

		if ((se->addr = (struct sockaddr_storage *) malloc (sizeof (struct sockaddr_storage))) == NULL)
		{
			char errbuf[1024];
			ERROR ("malloc: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			free (se);
			continue;
		}

		assert (sizeof (struct sockaddr_storage) >= ai_ptr->ai_addrlen);
		memset (se->addr, '\0', sizeof (struct sockaddr_storage));
		memcpy (se->addr, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
		se->addrlen = ai_ptr->ai_addrlen;

		se->fd   = socket (ai_ptr->ai_family,
				ai_ptr->ai_socktype,
				ai_ptr->ai_protocol);
		se->next = NULL;

		if (se->fd == -1)
		{
			char errbuf[1024];
			ERROR ("socket: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			free (se->addr);
			free (se);
			continue;
		}

		if (listen != 0)
		{
			if (network_bind_socket (se, ai_ptr) != 0)
			{
				close (se->fd);
				free (se->addr);
				free (se);
				continue;
			}
		}
		else /* listen == 0 */
		{
			network_set_ttl (se, ai_ptr);
		}

		if (se_tail == NULL)
		{
			se_head = se;
			se_tail = se;
		}
		else
		{
			se_tail->next = se;
			se_tail = se;
		}

		/* We don't open more than one write-socket per node/service pair.. */
		if (listen == 0)
			break;
	}

	freeaddrinfo (ai_list);

	return (se_head);
}