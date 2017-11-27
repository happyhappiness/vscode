static int riemann_send_msg (struct riemann_host *host, const Msg *msg) /* {{{ */
{
	int status = 0;
	u_char *buffer = NULL;
	size_t  buffer_len;

	status = riemann_connect (host);
	if (status != 0)
		return status;

	buffer_len = msg__get_packed_size(msg);

	if (host->use_tcp)
		buffer_len += 4;

	buffer = malloc (buffer_len);
	if (buffer == NULL) {
		ERROR ("write_riemann plugin: malloc failed.");
		return ENOMEM;
	}
	memset (buffer, 0, buffer_len);

	if (host->use_tcp)
	{
		uint32_t length = htonl ((uint32_t) (buffer_len - 4));
		memcpy (buffer, &length, 4);
		msg__pack(msg, buffer + 4);
	}
	else
	{
		msg__pack(msg, buffer);
	}

	status = (int) swrite (host->s, buffer, buffer_len);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR ("write_riemann plugin: Sending to Riemann at %s:%s failed: %s",
				(host->node != NULL) ? host->node : RIEMANN_HOST,
				(host->service != NULL) ? host->service : RIEMANN_PORT,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		sfree (buffer);
		return -1;
	}

	sfree (buffer);
	return 0;
}