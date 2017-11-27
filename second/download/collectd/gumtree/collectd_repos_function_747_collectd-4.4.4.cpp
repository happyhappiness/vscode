static int network_add_sending_socket (const char *node, const char *service)
{
	sockent_t *se;
	sockent_t *se_ptr;

	if (service == NULL)
		service = NET_DEFAULT_PORT;

	if (node == NULL)
		se = network_create_default_socket (0 /* listen == false */);
	else
		se = network_create_socket (node, service, 0 /* listen == false */);

	if (se == NULL)
		return (-1);

	if (sending_sockets == NULL)
	{
		sending_sockets = se;
		return (0);
	}

	for (se_ptr = sending_sockets; se_ptr->next != NULL; se_ptr = se_ptr->next)
		/* seek end */;

	se_ptr->next = se;
	return (0);
}