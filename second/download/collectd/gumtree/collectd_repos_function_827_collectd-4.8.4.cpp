static int tss2_config (const char *key, const char *value)
{
	/*
	 * Interpret configuration values
	 */
    if (strcasecmp ("Host", key) == 0)
	{
		char *temp;

		temp = strdup (value);
		if (temp == NULL)
		{
			ERROR("teamspeak2 plugin: strdup failed.");
			return (1);
		}
		sfree (config_host);
		config_host = temp;
	}
	else if (strcasecmp ("Port", key) == 0)
	{
		char *temp;

		temp = strdup (value);
		if (temp == NULL)
		{
			ERROR("teamspeak2 plugin: strdup failed.");
			return (1);
		}
		sfree (config_port);
		config_port = temp;
	}
	else if (strcasecmp ("Server", key) == 0)
	{
		/* Server variable found */
		int status;
		
		status = tss2_add_vserver (atoi (value));
		if (status != 0)
			return (1);
	}
	else
	{
		/* Unknown variable found */
		return (-1);
	}

	return 0;
}