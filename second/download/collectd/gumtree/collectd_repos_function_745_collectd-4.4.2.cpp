static sockent_t *network_create_default_socket (int listen)
{
	sockent_t *se_ptr  = NULL;
	sockent_t *se_head = NULL;
	sockent_t *se_tail = NULL;

	se_ptr = network_create_socket (NET_DEFAULT_V6_ADDR,
			NET_DEFAULT_PORT, listen);

	/* Don't send to the same machine in IPv6 and IPv4 if both are available. */
	if ((listen == 0) && (se_ptr != NULL))
		return (se_ptr);

	if (se_ptr != NULL)
	{
		se_head = se_ptr;
		se_tail = se_ptr;
		while (se_tail->next != NULL)
			se_tail = se_tail->next;
	}

	se_ptr = network_create_socket (NET_DEFAULT_V4_ADDR, NET_DEFAULT_PORT, listen);

	if (se_tail == NULL)
		return (se_ptr);

	se_tail->next = se_ptr;
	return (se_head);
}