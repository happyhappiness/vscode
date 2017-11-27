static int sockent_init (sockent_t *se, int type) /* {{{ */
{
	if (se == NULL)
		return (-1);

	memset (se, 0, sizeof (*se));

	se->type = SOCKENT_TYPE_CLIENT;
	se->node = NULL;
	se->service = NULL;
	se->next = NULL;

	if (type == SOCKENT_TYPE_SERVER)
	{
		se->type = SOCKENT_TYPE_SERVER;
		se->data.server.fd = NULL;
#if HAVE_LIBGCRYPT
		se->data.server.security_level = SECURITY_LEVEL_NONE;
		se->data.server.auth_file = NULL;
		se->data.server.userdb = NULL;
		se->data.server.cypher = NULL;
#endif
	}
	else
	{
		se->data.client.fd = -1;
		se->data.client.addr = NULL;
#if HAVE_LIBGCRYPT
		se->data.client.security_level = SECURITY_LEVEL_NONE;
		se->data.client.username = NULL;
		se->data.client.password = NULL;
		se->data.client.cypher = NULL;
#endif
	}

	return (0);
}