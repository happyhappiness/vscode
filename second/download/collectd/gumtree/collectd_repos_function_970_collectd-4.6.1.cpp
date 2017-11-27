static int network_receive (void)
{
	char buffer[BUFF_SIZE];
	int  buffer_len;

	int i;
	int status;

	receive_list_entry_t *private_list_head;
	receive_list_entry_t *private_list_tail;

	if (listen_sockets_num == 0)
		network_add_listen_socket (NULL, NULL);

	if (listen_sockets_num == 0)
	{
		ERROR ("network: Failed to open a listening socket.");
		return (-1);
	}

	private_list_head = NULL;
	private_list_tail = NULL;

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
			receive_list_entry_t *ent;

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

			ent = malloc (sizeof (receive_list_entry_t));
			if (ent == NULL)
			{
				ERROR ("network plugin: malloc failed.");
				return (-1);
			}
			memset (ent, 0, sizeof (receive_list_entry_t));
			ent->next = NULL;

			/* Hopefully this be optimized out by the compiler. It
			 * might help prevent stupid bugs in the future though.
			 */
			assert (sizeof (ent->data) == sizeof (buffer));

			memcpy (ent->data, buffer, buffer_len);
			ent->data_len = buffer_len;

			if (private_list_head == NULL)
				private_list_head = ent;
			else
				private_list_tail->next = ent;
			private_list_tail = ent;

			/* Do not block here. Blocking here has led to
			 * insufficient performance in the past. */
			if (pthread_mutex_trylock (&receive_list_lock) == 0)
			{
				if (receive_list_head == NULL)
					receive_list_head = private_list_head;
				else
					receive_list_tail->next = private_list_head;
				receive_list_tail = private_list_tail;

				private_list_head = NULL;
				private_list_tail = NULL;

				pthread_cond_signal (&receive_list_cond);
				pthread_mutex_unlock (&receive_list_lock);
			}
		} /* for (listen_sockets) */
	} /* while (listen_loop == 0) */

	/* Make sure everything is dispatched before exiting. */
	if (private_list_head != NULL)
	{
		pthread_mutex_lock (&receive_list_lock);

		if (receive_list_head == NULL)
			receive_list_head = private_list_head;
		else
			receive_list_tail->next = private_list_head;
		receive_list_tail = private_list_tail;

		private_list_head = NULL;
		private_list_tail = NULL;

		pthread_cond_signal (&receive_list_cond);
		pthread_mutex_unlock (&receive_list_lock);
	}

	return (0);
}