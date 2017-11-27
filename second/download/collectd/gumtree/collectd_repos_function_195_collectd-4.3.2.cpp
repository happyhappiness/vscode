static int us_handle_getval (FILE *fh, char **fields, int fields_num)
{
	char *hostname;
	char *plugin;
	char *plugin_instance;
	char *type;
	char *type_instance;
	char  name[4*DATA_MAX_NAME_LEN];
	value_cache_t *vc;
	int   status;
	int   i;

	if (fields_num != 2)
	{
		DEBUG ("unixsock plugin: Wrong number of fields: %i", fields_num);
		fprintf (fh, "-1 Wrong number of fields: Got %i, expected 2.\n",
				fields_num);
		fflush (fh);
		return (-1);
	}
	DEBUG ("unixsock plugin: Got query for `%s'", fields[1]);

	status = parse_identifier (fields[1], &hostname,
			&plugin, &plugin_instance,
			&type, &type_instance);
	if (status != 0)
	{
		DEBUG ("unixsock plugin: Cannot parse `%s'", fields[1]);
		fprintf (fh, "-1 Cannot parse identifier.\n");
		fflush (fh);
		return (-1);
	}

	status = format_name (name, sizeof (name),
			hostname, plugin, plugin_instance, type, type_instance);
	if (status != 0)
	{
		fprintf (fh, "-1 format_name failed.\n");
		return (-1);
	}

	pthread_mutex_lock (&cache_lock);

	DEBUG ("vc = cache_search (%s)", name);
	vc = cache_search (name);

	if (vc == NULL)
	{
		DEBUG ("Did not find cache entry.");
		fprintf (fh, "-1 No such value");
	}
	else
	{
		DEBUG ("Found cache entry.");
		fprintf (fh, "%i", vc->values_num);
		for (i = 0; i < vc->values_num; i++)
		{
			fprintf (fh, " %s=", vc->ds->ds[i].name);
			if (isnan (vc->gauge[i]))
				fprintf (fh, "NaN");
			else
				fprintf (fh, "%12e", vc->gauge[i]);
		}
	}

	/* Free the mutex as soon as possible and definitely before flushing */
	pthread_mutex_unlock (&cache_lock);

	fprintf (fh, "\n");
	fflush (fh);

	return (0);
}