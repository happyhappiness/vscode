static int ntpd_receive_response (int req_code, int *res_items, int *res_size,
		char **res_data, int res_item_size)
{
	int              sd;
	struct pollfd    poll_s;
	struct resp_pkt  res;
	int              status;
	int              done;
	int              i;

	char            *items;
	size_t           items_num;

	struct timeval   time_end;
	struct timeval   time_now;
	int              timeout;

	int              pkt_item_num;        /* items in this packet */
	int              pkt_item_len;        /* size of the items in this packet */
	int              pkt_sequence;
	char             pkt_recvd[MAXSEQ+1]; /* sequence numbers that have been received */
	int              pkt_recvd_num;       /* number of packets that have been received */
	int              pkt_lastseq;         /* the last sequence number */
	ssize_t          pkt_padding;         /* Padding in this packet */

	if ((sd = ntpd_connect ()) < 0)
		return (-1);

	items = NULL;
	items_num = 0;

	memset (pkt_recvd, '\0', sizeof (pkt_recvd));
	pkt_recvd_num = 0;
	pkt_lastseq   = -1;

	*res_items = 0;
	*res_size  = 0;
	*res_data  = NULL;

	if (gettimeofday (&time_end, NULL) < 0)
	{
		char errbuf[1024];
		ERROR ("ntpd plugin: gettimeofday failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}
	time_end.tv_sec++; /* wait for a most one second */

	done = 0;
	while (done == 0)
	{
		if (gettimeofday (&time_now, NULL) < 0)
		{
			char errbuf[1024];
			ERROR ("ntpd plugin: gettimeofday failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return (-1);
		}

		/* timeout reached */
		if ((timeout = timeval_sub (&time_end, &time_now)) == 0)
			break;

		poll_s.fd      = sd;
		poll_s.events  = POLLIN | POLLPRI;
		poll_s.revents = 0;
		
		DEBUG ("Polling for %ims", timeout);
		status = poll (&poll_s, 1, timeout);

		if ((status < 0) && ((errno == EAGAIN) || (errno == EINTR)))
			continue;

		if (status < 0)
		{
			char errbuf[1024];
			ERROR ("ntpd plugin: poll failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return (-1);
		}

		if (status == 0) /* timeout */
		{
			DEBUG ("timeout reached.");
			break;
		}

		memset ((void *) &res, '\0', sizeof (res));
		status = recv (sd, (void *) &res, sizeof (res), 0 /* no flags */);

		if ((status < 0) && ((errno == EAGAIN) || (errno == EINTR)))
			continue;

		if (status < 0)
		{
			char errbuf[1024];
			DEBUG ("recv(2) failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			DEBUG ("Closing socket #%i", sd);
			close (sd);
			sock_descr = sd = -1;
			return (-1);
		}

		DEBUG ("recv'd %i bytes", status);

		/* 
		 * Do some sanity checks first
		 */
		if (status < RESP_HEADER_SIZE)
		{
			WARNING ("ntpd plugin: Short (%i bytes) packet received",
					(int) status);
			continue;
		}
		if (INFO_MODE (res.rm_vn_mode) != MODE_PRIVATE)
		{
			NOTICE ("ntpd plugin: Packet received with mode %i",
					INFO_MODE (res.rm_vn_mode));
			continue;
		}
		if (INFO_IS_AUTH (res.auth_seq))
		{
			NOTICE ("ntpd plugin: Encrypted packet received");
			continue;
		}
		if (!ISRESPONSE (res.rm_vn_mode))
		{
			NOTICE ("ntpd plugin: Received request packet, "
					"wanted response");
			continue;
		}
		if (INFO_MBZ (res.mbz_itemsize))
		{
			WARNING ("ntpd plugin: Received packet with nonzero "
					"MBZ field!");
			continue;
		}
		if (res.implementation != IMPL_XNTPD)
		{
			WARNING ("ntpd plugin: Asked for request of type %i, "
					"got %i", (int) IMPL_XNTPD, (int) res.implementation);
			continue;
		}

		/* Check for error code */
		if (INFO_ERR (res.err_nitems) != 0)
		{
			ERROR ("ntpd plugin: Received error code %i",
					(int) INFO_ERR(res.err_nitems));
			return ((int) INFO_ERR (res.err_nitems));
		}

		/* extract number of items in this packet and the size of these items */
		pkt_item_num = INFO_NITEMS (res.err_nitems);
		pkt_item_len = INFO_ITEMSIZE (res.mbz_itemsize);
		DEBUG ("pkt_item_num = %i; pkt_item_len = %i;",
				pkt_item_num, pkt_item_len);

		/* Check if the reported items fit in the packet */
		if ((pkt_item_num * pkt_item_len) > (status - RESP_HEADER_SIZE))
		{
			ERROR ("ntpd plugin: %i items * %i bytes > "
					"%i bytes - %i bytes header",
					(int) pkt_item_num, (int) pkt_item_len,
					(int) status, (int) RESP_HEADER_SIZE);
			continue;
		}

		if (pkt_item_len > res_item_size)
		{
			ERROR ("ntpd plugin: (pkt_item_len = %i) "
					">= (res_item_size = %i)",
					pkt_item_len, res_item_size);
			continue;
		}

		/* If this is the first packet (time wise, not sequence wise),
		 * set `res_size'. If it's not the first packet check if the
		 * items have the same size. Discard invalid packets. */
		if (items_num == 0) /* first packet */
		{
			DEBUG ("*res_size = %i", pkt_item_len);
			*res_size = pkt_item_len;
		}
		else if (*res_size != pkt_item_len)
		{
			DEBUG ("Error: *res_size = %i; pkt_item_len = %i;",
					*res_size, pkt_item_len);
			ERROR ("Item sizes differ.");
			continue;
		}

		/*
		 * Because the items in the packet may be smaller than the
		 * items requested, the following holds true:
		 */
		assert ((*res_size == pkt_item_len)
				&& (pkt_item_len <= res_item_size));

		/* Calculate the padding. No idea why there might be any padding.. */
		pkt_padding = 0;
		if (pkt_item_len < res_item_size)
			pkt_padding = res_item_size - pkt_item_len;
		DEBUG ("res_item_size = %i; pkt_padding = %i;",
				res_item_size, pkt_padding);

		/* Extract the sequence number */
		pkt_sequence = INFO_SEQ (res.auth_seq);
		if ((pkt_sequence < 0) || (pkt_sequence > MAXSEQ))
		{
			ERROR ("ntpd plugin: Received packet with sequence %i",
					pkt_sequence);
			continue;
		}

		/* Check if this sequence has been received before. If so, discard it. */
		if (pkt_recvd[pkt_sequence] != '\0')
		{
			NOTICE ("ntpd plugin: Sequence %i received twice",
					pkt_sequence);
			continue;
		}

		/* If `pkt_lastseq != -1' another packet without `more bit' has
		 * been received. */
		if (!ISMORE (res.rm_vn_mode))
		{
			if (pkt_lastseq != -1)
			{
				ERROR ("ntpd plugin: Two packets which both "
						"claim to be the last one in the "
						"sequence have been received.");
				continue;
			}
			pkt_lastseq = pkt_sequence;
			DEBUG ("Last sequence = %i;", pkt_lastseq);
		}

		/*
		 * Enough with the checks. Copy the data now.
		 * We start by allocating some more memory.
		 */
		DEBUG ("realloc (%p, %i)", (void *) *res_data,
				(items_num + pkt_item_num) * res_item_size);
		items = realloc ((void *) *res_data,
				(items_num + pkt_item_num) * res_item_size);
		if (items == NULL)
		{
			items = *res_data;
			ERROR ("ntpd plugin: realloc failed.");
			continue;
		}
		items_num += pkt_item_num;
		*res_data = items;

		for (i = 0; i < pkt_item_num; i++)
		{
			/* dst: There are already `*res_items' items with
			 *      res_item_size bytes each in in `*res_data'. Set
			 *      dst to the first byte after that. */
			void *dst = (void *) (*res_data + ((*res_items) * res_item_size));
			/* src: We use `pkt_item_len' to calculate the offset
			 *      from the beginning of the packet, because the
			 *      items in the packet may be smaller than the
			 *      items that were requested. We skip `i' such
			 *      items. */
			void *src = (void *) (((char *) res.data) + (i * pkt_item_len));

			/* Set the padding to zeros */
			if (pkt_padding != 0)
				memset (dst, '\0', res_item_size);
			memcpy (dst, src, (size_t) pkt_item_len);

			/* Increment `*res_items' by one, so `dst' will end up
			 * one further in the next round. */
			(*res_items)++;
		} /* for (pkt_item_num) */

		pkt_recvd[pkt_sequence] = (char) 1;
		pkt_recvd_num++;

		if ((pkt_recvd_num - 1) == pkt_lastseq)
			done = 1;
	} /* while (done == 0) */

	return (0);
}