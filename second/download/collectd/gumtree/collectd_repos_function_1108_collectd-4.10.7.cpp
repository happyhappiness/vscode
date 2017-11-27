static int hddtemp_config (const char *key, const char *value)
{
	if (strcasecmp (key, "Host") == 0)
	{
		if (hddtemp_host != NULL)
			free (hddtemp_host);
		hddtemp_host = strdup (value);
	}
	else if (strcasecmp (key, "Port") == 0)
	{
		int port = (int) (atof (value));
		if ((port > 0) && (port <= 65535))
			ssnprintf (hddtemp_port, sizeof (hddtemp_port),
					"%i", port);
		else
			sstrncpy (hddtemp_port, value, sizeof (hddtemp_port));
	}
	else if (strcasecmp (key, "TranslateDevicename") == 0)
	{
		if (IS_TRUE (value))
			translate_devicename = 1;
		else
			translate_devicename = 0;
	}
	else
	{
		return (-1);
	}

	return (0);
}