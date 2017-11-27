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

		/* Convert the `long floating point' offset value to double */
		M_LFPTOD (ntohl (ptr->offset_int), ntohl (ptr->offset_frc), offset);

		/* Special IP addresses for hardware clocks and stuff.. */
		if (!ptr->v6_flag
				&& ((ntohl (ptr->srcadr) & REFCLOCK_MASK)
					== REFCLOCK_ADDR))
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
		else /* Normal network host. */
		{
			struct sockaddr_storage sa;
			socklen_t sa_len;
			int flags = 0;

			memset (&sa, '\0', sizeof (sa));

			if (ptr->v6_flag)
			{
				struct sockaddr_in6 *sa_ptr;
				sa_ptr = (struct sockaddr_in6 *) &sa;

				sa_ptr->sin6_family = AF_INET6;
				sa_ptr->sin6_port = htons (123);
				memcpy (&sa_ptr->sin6_addr, &ptr->srcadr6,
						sizeof (struct in6_addr));
				sa_len = sizeof (struct sockaddr_in6);
			}
			else
			{
				struct sockaddr_in *sa_ptr;
				sa_ptr = (struct sockaddr_in *) &sa;

				sa_ptr->sin_family = AF_INET;
				sa_ptr->sin_port = htons (123);
				memcpy (&sa_ptr->sin_addr, &ptr->srcadr,
						sizeof (struct in_addr));
				sa_len = sizeof (struct sockaddr_in);
			}

			if (do_reverse_lookups == 0)
				flags |= NI_NUMERICHOST;

			status = getnameinfo ((const struct sockaddr *) &sa,
					sa_len,
					peername, sizeof (peername),
					NULL, 0, /* No port name */
					flags);
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