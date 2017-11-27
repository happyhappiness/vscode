static int network_receive (void)
{
	char buffer[BUFF_SIZE];
	int  buffer_len;

	int i;
	int status;

	if (listen_sockets_num == 0)
		network_add_listen_socket (NULL, NULL);

	if (listen_sockets_num == 0)
	{
		ERROR ("network: Failed to open a listening socket.");
		return (-1);
	}

	while (listen_loop == 0)
	{
		status = poll (listen_sockets, listen_sockets_num, -1);

		if (status <= 0)
		{
			char errbuf[1024];
			if (errno == EINTR)
				continue;
			ERROR ("poll failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return (-1);
		}

		for (i = 0; (i < listen_sockets_num) && (status > 0); i++)
		{
			if ((listen_sockets[i].revents & (POLLIN | POLLPRI)) == 0)
				continue;
			status--;

			buffer_len = recv (listen_sockets[i].fd,
					buffer, sizeof (buffer),
					0 /* no flags */);
			if (buffer_len < 0)
			{
				char errbuf[1024];
				ERROR ("recv failed: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}

			parse_packet (buffer, buffer_len);
		} /* for (listen_sockets) */
	} /* while (listen_loop == 0) */

	return (0);
}