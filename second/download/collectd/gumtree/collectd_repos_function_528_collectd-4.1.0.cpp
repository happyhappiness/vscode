static int ntpd_read (void)
{
	struct info_kernel *ik;
	int                 ik_num;
	int                 ik_size;

	struct info_peer_summary *ps;
	int                       ps_num;
	int                       ps_size;

	int status;
	int i;

	ik      = NULL;
	ik_num  = 0;
	ik_size = 0;

	status = ntpd_do_query (REQ_GET_KERNEL,
			0, 0, NULL, /* request data */
			&ik_num, &ik_size, (char **) ((void *) &ik), /* response data */
			sizeof (struct info_kernel));

	if (status != 0)
	{
		DEBUG ("ntpd_do_query failed with status %i", status);
		return (-1);
	}
	if ((ik == NULL) || (ik_num == 0) || (ik_size == 0))
	{
		DEBUG ("ntpd_do_query returned: ik = %p; ik_num = %i; ik_size = %i;",
				(void *) ik, ik_num, ik_size);
		return (-1);
	}

	/* kerninfo -> estimated error */

	DEBUG ("info_kernel:\n"
			"  pll offset    = %.8f\n"
			"  pll frequency = %.8f\n" /* drift compensation */
			"  est error     = %.8f\n",
			ntpd_read_fp (ik->offset),
			ntpd_read_fp (ik->freq),
			ntpd_read_fp (ik->esterror));

	ntpd_submit ("frequency_offset", "loop",  ntpd_read_fp (ik->freq));
	ntpd_submit ("time_offset",      "loop",  ntpd_read_fp (ik->offset));
	ntpd_submit ("time_offset",      "error", ntpd_read_fp (ik->esterror));

	free (ik);
	ik = NULL;

	status = ntpd_do_query (REQ_PEER_LIST_SUM,
			0, 0, NULL, /* request data */
			&ps_num, &ps_size, (char **) ((void *) &ps), /* response data */
			sizeof (struct info_peer_summary));
	if (status != 0)
	{
		DEBUG ("ntpd_do_query failed with status %i", status);
		return (-1);
	}
	if ((ps == NULL) || (ps_num == 0) || (ps_size == 0))
	{
		DEBUG ("ntpd_do_query returned: ps = %p; ps_num = %i; ps_size = %i;",
				(void *) ps, ps_num, ps_size);
		return (-1);
	}

	for (i = 0; i < ps_num; i++)
	{
		struct info_peer_summary *ptr;
		double offset;

		char peername[NI_MAXHOST];
		int refclock_id;
		
		ptr = ps + i;
		refclock_id = 0;

		/*
		if (((ntohl (ptr->dstadr) & 0xFFFFFF00) == 0x7F000000) || (ptr->dstadr == 0))
			continue;
			*/

		/* Convert the `long floating point' offset value to double */
		M_LFPTOD (ntohl (ptr->offset_int), ntohl (ptr->offset_frc), offset);

		if (ptr->v6_flag)
		{
			struct sockaddr_in6 sa;

			memset (&sa, 0, sizeof (sa));
			sa.sin6_family = AF_INET6;
			sa.sin6_port = htons (123);
			memcpy (&sa.sin6_addr, &ptr->srcadr6, sizeof (struct in6_addr));

			status = getnameinfo ((const struct sockaddr *) &sa,
					sizeof (sa),
					peername, sizeof (peername),
					NULL, 0, 0 /* no flags */);
			if (status != 0)
			{
				char errbuf[1024];
				ERROR ("ntpd plugin: getnameinfo failed: %s",
						(status == EAI_SYSTEM)
						? sstrerror (errno, errbuf, sizeof (errbuf))
						: gai_strerror (status));
				continue;
			}
		}
		else if ((ntohl (ptr->srcadr) & REFCLOCK_MASK) == REFCLOCK_ADDR)
		{
			struct in_addr  addr_obj;
			char *addr_str;

			refclock_id = (ntohl (ptr->srcadr) >> 8) & 0x000000FF;

			if (refclock_id < refclock_names_num)
			{
				strncpy (peername, refclock_names[refclock_id],
						sizeof (peername));
			}
			else
			{
				memset ((void *) &addr_obj, '\0', sizeof (addr_obj));
				addr_obj.s_addr = ptr->srcadr;
				addr_str = inet_ntoa (addr_obj);

				strncpy (peername, addr_str, sizeof (peername));
			}
		}
		else /* IPv4 */
		{
			struct in_addr  addr_obj;
			struct hostent *addr_he;
			char           *addr_str;

			memset ((void *) &addr_obj, '\0', sizeof (addr_obj));
			addr_obj.s_addr = ptr->srcadr;
			addr_str = inet_ntoa (addr_obj);

			addr_he = gethostbyaddr ((const void *) &addr_obj,
					sizeof (addr_obj), AF_INET);
			if (addr_he != NULL)
			{
				strncpy (peername, addr_he->h_name, sizeof (peername));
			}
			else
			{
				strncpy (peername, addr_str, sizeof (peername));
			}
		}

		DEBUG ("peer %i:\n"
				"  peername   = %s\n"
				"  srcadr     = 0x%08x\n"
				"  delay      = %f\n"
				"  offset_int = %i\n"
				"  offset_frc = %i\n"
				"  offset     = %f\n"
				"  dispersion = %f\n",
				i,
				peername,
				ntohl (ptr->srcadr),
				ntpd_read_fp (ptr->delay),
				ntohl (ptr->offset_int),
				ntohl (ptr->offset_frc),
				offset,
				ntpd_read_fp (ptr->dispersion));

		if (refclock_id != 1) /* not the system clock (offset will always be zero.. */
			ntpd_submit ("time_offset", peername, offset);
		ntpd_submit ("time_dispersion", peername, ntpd_read_fp (ptr->dispersion));
		if (refclock_id == 0) /* not a reference clock */
			ntpd_submit ("delay", peername, ntpd_read_fp (ptr->delay));
	}

	free (ps);
	ps = NULL;

	return (0);
}