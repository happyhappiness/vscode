static int network_config (const char *key, const char *val)
{
	char *node;
	char *service;

	char *fields[3];
	int   fields_num;

	if ((strcasecmp ("Listen", key) == 0)
			|| (strcasecmp ("Server", key) == 0))
	{
		char *val_cpy = strdup (val);
		if (val_cpy == NULL)
			return (1);

		service = NET_DEFAULT_PORT;
		fields_num = strsplit (val_cpy, fields, 3);
		if ((fields_num != 1)
				&& (fields_num != 2))
			return (1);
		else if (fields_num == 2)
		{
			if ((service = strchr (fields[1], '.')) != NULL)
				*service = '\0';
			service = fields[1];
		}
		node = fields[0];

		if (strcasecmp ("Listen", key) == 0)
			network_add_listen_socket (node, service);
		else
			network_add_sending_socket (node, service);
	}
	else if (strcasecmp ("TimeToLive", key) == 0)
	{
		int tmp = atoi (val);
		if ((tmp > 0) && (tmp < 256))
			network_config_ttl = tmp;
		else
			return (1);
	}
	else if (strcasecmp ("Forward", key) == 0)
	{
		if ((strcasecmp ("true", val) == 0)
				|| (strcasecmp ("yes", val) == 0)
				|| (strcasecmp ("on", val) == 0))
			network_config_forward = 1;
		else
			network_config_forward = 0;
	}
	else if (strcasecmp ("CacheFlush", key) == 0)
	{
		int tmp = atoi (val);
		if (tmp > 0)
			cache_flush_interval = tmp;
		else return (1);
	}
	else
	{
		return (-1);
	}
	return (0);
}