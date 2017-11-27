static int apcups_config (const char *key, const char *value)
{
	if (strcasecmp (key, "host") == 0)
	{
		if (conf_host != NULL)
		{
			free (conf_host);
			conf_host = NULL;
		}
		if ((conf_host = strdup (value)) == NULL)
			return (1);
	}
	else if (strcasecmp (key, "Port") == 0)
	{
		int port_tmp = atoi (value);
		if (port_tmp < 1 || port_tmp > 65535)
		{
			WARNING ("apcups plugin: Invalid port: %i", port_tmp);
			return (1);
		}
		conf_port = port_tmp;
	}
	else
	{
		return (-1);
	}
	return (0);
}