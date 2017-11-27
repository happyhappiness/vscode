static int sockent_open (sockent_t *se) /* {{{ */
{
	struct addrinfo  ai_hints;
	struct addrinfo *ai_list, *ai_ptr;
	int              ai_return;

        const char *node;
        const char *service;

	if (se == NULL)
		return (-1);

	/* Set up the security structures. */
#if HAVE_LIBGCRYPT /* {{{ */
	if (se->type == SOCKENT_TYPE_CLIENT)
	{
		if (se->data.client.security_level > SECURITY_LEVEL_NONE)
		{
			if ((se->data.client.username == NULL)
					|| (se->data.client.password == NULL))
			{
				ERROR ("network plugin: Client socket with "
						"security requested, but no "
						"credentials are configured.");
				return (-1);
			}
			gcry_md_hash_buffer (GCRY_MD_SHA256,
					se->data.client.password_hash,
					se->data.client.password,
					strlen (se->data.client.password));
		}
	}
	else /* (se->type == SOCKENT_TYPE_SERVER) */
	{
		if (se->data.server.security_level > SECURITY_LEVEL_NONE)
		{
			if (se->data.server.auth_file == NULL)
			{
				ERROR ("network plugin: Server socket with "
						"security requested, but no "
						"password file is configured.");
				return (-1);
			}
		}
		if (se->data.server.auth_file != NULL)
		{
			se->data.server.userdb = fbh_create (se->data.server.auth_file);
			if (se->data.server.userdb == NULL)
			{
				ERROR ("network plugin: Reading password file "
						"`%s' failed.",
						se->data.server.auth_file);
				if (se->data.server.security_level > SECURITY_LEVEL_NONE)
					return (-1);
			}
		}
	}
#endif /* }}} HAVE_LIBGCRYPT */

        node = se->node;
        service = se->service;

        if (service == NULL)
          service = NET_DEFAULT_PORT;

        DEBUG ("network plugin: sockent_open: node = %s; service = %s;",
            node, service);

	memset (&ai_hints, 0, sizeof (ai_hints));
	ai_hints.ai_flags  = 0;
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
		ERROR ("network plugin: getaddrinfo (%s, %s) failed: %s",
				(se->node == NULL) ? "(null)" : se->node,
				(se->service == NULL) ? "(null)" : se->service,
				gai_strerror (ai_return));
		return (-1);
	}

	for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		int status;

		if (se->type == SOCKENT_TYPE_SERVER) /* {{{ */
		{
			int *tmp;

			tmp = realloc (se->data.server.fd,
					sizeof (*tmp) * (se->data.server.fd_num + 1));
			if (tmp == NULL)
			{
				ERROR ("network plugin: realloc failed.");
				continue;
			}
			se->data.server.fd = tmp;
			tmp = se->data.server.fd + se->data.server.fd_num;

			*tmp = socket (ai_ptr->ai_family, ai_ptr->ai_socktype,
					ai_ptr->ai_protocol);
			if (*tmp < 0)
			{
				char errbuf[1024];
				ERROR ("network plugin: socket(2) failed: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				continue;
			}

			status = network_bind_socket (*tmp, ai_ptr, se->interface);
			if (status != 0)
			{
				close (*tmp);
				*tmp = -1;
				continue;
			}

			se->data.server.fd_num++;
			continue;
		} /* }}} if (se->type == SOCKENT_TYPE_SERVER) */
		else /* if (se->type == SOCKENT_TYPE_CLIENT) {{{ */
		{
			se->data.client.fd = socket (ai_ptr->ai_family,
					ai_ptr->ai_socktype,
					ai_ptr->ai_protocol);
			if (se->data.client.fd < 0)
			{
				char errbuf[1024];
				ERROR ("network plugin: socket(2) failed: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				continue;
			}

			se->data.client.addr = malloc (sizeof (*se->data.client.addr));
			if (se->data.client.addr == NULL)
			{
				ERROR ("network plugin: malloc failed.");
				close (se->data.client.fd);
				se->data.client.fd = -1;
				continue;
			}

			memset (se->data.client.addr, 0, sizeof (*se->data.client.addr));
			assert (sizeof (*se->data.client.addr) >= ai_ptr->ai_addrlen);
			memcpy (se->data.client.addr, ai_ptr->ai_addr, ai_ptr->ai_addrlen);
			se->data.client.addrlen = ai_ptr->ai_addrlen;

			network_set_ttl (se, ai_ptr);
			network_set_interface (se, ai_ptr);

			/* We don't open more than one write-socket per
			 * node/service pair.. */
			break;
		} /* }}} if (se->type == SOCKENT_TYPE_CLIENT) */
	} /* for (ai_list) */

	freeaddrinfo (ai_list);

	/* Check if all went well. */
	if (se->type == SOCKENT_TYPE_SERVER)
	{
		if (se->data.server.fd_num <= 0)
			return (-1);
	}
	else /* if (se->type == SOCKENT_TYPE_CLIENT) */
	{
		if (se->data.client.fd < 0)
			return (-1);
	}

	return (0);
}