static void network_send_buffer (const char *buffer, int buffer_len)
{
	sockent_t *se;
	int status;

	DEBUG ("network plugin: network_send_buffer: buffer_len = %i", buffer_len);

	for (se = sending_sockets; se != NULL; se = se->next)
	{
		while (42)
		{
			status = sendto (se->fd, buffer, buffer_len, 0 /* no flags */,
					(struct sockaddr *) se->addr, se->addrlen);
			if (status < 0)
			{
				char errbuf[1024];
				if (errno == EINTR)
					continue;
				ERROR ("network plugin: sendto failed: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				break;
			}

			break;
		} /* while (42) */
	} /* for (sending_sockets) */
}