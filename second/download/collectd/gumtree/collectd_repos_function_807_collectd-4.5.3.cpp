static int csv_config (const char *key, const char *value)
{
	if (strcasecmp ("DataDir", key) == 0)
	{
		if (datadir != NULL)
			free (datadir);
		datadir = strdup (value);
		if (datadir != NULL)
		{
			int len = strlen (datadir);
			while ((len > 0) && (datadir[len - 1] == '/'))
			{
				len--;
				datadir[len] = '\0';
			}
			if (len <= 0)
			{
				free (datadir);
				datadir = NULL;
			}
		}
	}
	else if (strcasecmp ("StoreRates", key) == 0)
	{
		if ((strcasecmp ("True", value) == 0)
				|| (strcasecmp ("Yes", value) == 0)
				|| (strcasecmp ("On", value) == 0))
		{
			store_rates = 1;
		}
		else
		{
			store_rates = 0;
		}
	}
	else
	{
		return (-1);
	}
	return (0);
}