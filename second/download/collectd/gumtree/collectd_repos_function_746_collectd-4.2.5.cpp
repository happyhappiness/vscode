int ping_iterator_get_info (pingobj_iter_t *iter, int info,
		void *buffer, size_t *buffer_len)
{
	int ret = EINVAL;

	size_t orig_buffer_len = *buffer_len;

	switch (info)
	{
		case PING_INFO_HOSTNAME:
			ret = ENOMEM;
			*buffer_len = strlen (iter->hostname);
			if (orig_buffer_len <= *buffer_len)
				break;
			/* Since (orig_buffer_len > *buffer_len) `strncpy'
			 * will copy `*buffer_len' and pad the rest of
			 * `buffer' with null-bytes */
			strncpy (buffer, iter->hostname, orig_buffer_len);
			ret = 0;
			break;

		case PING_INFO_ADDRESS:
			ret = getnameinfo ((struct sockaddr *) iter->addr,
					iter->addrlen,
					(char *) buffer,
					*buffer_len,
					NULL, 0,
					NI_NUMERICHOST);
			if (ret != 0)
			{
				if ((ret == EAI_MEMORY)
#ifdef EAI_OVERFLOW
						|| (ret == EAI_OVERFLOW)
#endif
				   )
					ret = ENOMEM;
				else if (ret == EAI_SYSTEM)
					/* XXX: Not thread-safe! */
					ret = errno;
				else
					ret = EINVAL;
			}
			break;

		case PING_INFO_FAMILY:
			ret = ENOMEM;
			*buffer_len = sizeof (int);
			if (orig_buffer_len < sizeof (int))
				break;
			*((int *) buffer) = iter->addrfamily;
			ret = 0;
			break;

		case PING_INFO_LATENCY:
			ret = ENOMEM;
			*buffer_len = sizeof (double);
			if (orig_buffer_len < sizeof (double))
				break;
			*((double *) buffer) = iter->latency;
			ret = 0;
			break;

		case PING_INFO_SEQUENCE:
			ret = ENOMEM;
			*buffer_len = sizeof (unsigned int);
			if (orig_buffer_len < sizeof (unsigned int))
				break;
			*((unsigned int *) buffer) = (unsigned int) iter->sequence;
			ret = 0;
			break;

		case PING_INFO_IDENT:
			ret = ENOMEM;
			*buffer_len = sizeof (uint16_t);
			if (orig_buffer_len < sizeof (uint16_t))
				break;
			*((uint16_t *) buffer) = (uint16_t) iter->ident;
			ret = 0;
			break;

		case PING_INFO_DATA:
			ret = ENOMEM;
			*buffer_len = strlen (iter->data);
			if (orig_buffer_len < *buffer_len)
				break;
			strncpy ((char *) buffer, iter->data, orig_buffer_len);
			ret = 0;
			break;
	}

	return (ret);
}