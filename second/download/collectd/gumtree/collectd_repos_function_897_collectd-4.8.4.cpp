static void tt_open_db (void)
{
	char* host = NULL;
	int   port = DEFAULT_PORT;

	if (rdb != NULL)
		return;

	host = ((config_host != NULL) ? config_host : DEFAULT_HOST);

	if (config_port != NULL)
	{
		port = parse_service_name (config_port);
		if (port <= 0)
			return;
	}

	rdb = tcrdbnew ();
	if (rdb == NULL)
		return;
	else if (!tcrdbopen(rdb, host, port))
	{
		printerr ();
		tcrdbdel (rdb);
		rdb = NULL;
	}
}