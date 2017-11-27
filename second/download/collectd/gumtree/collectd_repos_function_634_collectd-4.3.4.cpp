static int ntpd_config (const char *key, const char *value)
{
	if (strcasecmp (key, "Host") == 0)
	{
		if (ntpd_host != NULL)
			free (ntpd_host);
		if ((ntpd_host = strdup (value)) == NULL)
			return (1);
	}
	else if (strcasecmp (key, "Port") == 0)
	{
		int port = (int) (atof (value));
		if ((port > 0) && (port <= 65535))
			snprintf (ntpd_port, sizeof (ntpd_port),
					"%i", port);
		else
			strncpy (ntpd_port, value, sizeof (ntpd_port));
		ntpd_port[sizeof (ntpd_port) - 1] = '\0';
	}
	else if (strcasecmp (key, "ReverseLookups") == 0)
	{
		if ((strcasecmp (value, "True") == 0)
				|| (strcasecmp (value, "Yes") == 0)
				|| (strcasecmp (value, "On") == 0))
			do_reverse_lookups = 1;
		else
			do_reverse_lookups = 0;
	}
	else
	{
		return (-1);
	}

	return (0);
}