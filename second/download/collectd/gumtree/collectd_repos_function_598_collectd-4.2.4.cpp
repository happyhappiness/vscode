static int network_add_listen_socket (const char *node, const char *service)
{
	sockent_t *se;
	sockent_t *se_ptr;
	int se_num = 0;

	if (service == NULL)
		service = NET_DEFAULT_PORT;

	if (node == NULL)
		se = network_create_default_socket (1 /* listen == true */);
	else
		se = network_create_socket (node, service, 1 /* listen == true */);

	if (se == NULL)
		return (-1);

	for (se_ptr = se; se_ptr != NULL; se_ptr = se_ptr->next)
		se_num++;

	listen_sockets = (struct pollfd *) realloc (listen_sockets,
			(listen_sockets_num + se_num)
			* sizeof (struct pollfd));

	for (se_ptr = se; se_ptr != NULL; se_ptr = se_ptr->next)
	{
		listen_sockets[listen_sockets_num].fd = se_ptr->fd;
		listen_sockets[listen_sockets_num].events = POLLIN | POLLPRI;
		listen_sockets[listen_sockets_num].revents = 0;
		listen_sockets_num++;
	} /* for (se) */

	free_sockent (se);
	return (0);
}