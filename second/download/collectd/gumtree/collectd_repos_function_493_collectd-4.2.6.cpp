static int ds_get (char ***ret, const data_set_t *ds, const value_list_t *vl)
{
	char **ds_def;
	int ds_num;

	char min[32];
	char max[32];
	char buffer[128];

	DEBUG ("ds->ds_num = %i", ds->ds_num);

	ds_def = (char **) malloc (ds->ds_num * sizeof (char *));
	if (ds_def == NULL)
	{
		char errbuf[1024];
		ERROR ("rrdtool plugin: malloc failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}
	memset (ds_def, '\0', ds->ds_num * sizeof (char *));

	for (ds_num = 0; ds_num < ds->ds_num; ds_num++)
	{
		data_source_t *d = ds->ds + ds_num;
		char *type;
		int status;

		ds_def[ds_num] = NULL;

		if (d->type == DS_TYPE_COUNTER)
			type = "COUNTER";
		else if (d->type == DS_TYPE_GAUGE)
			type = "GAUGE";
		else
		{
			ERROR ("rrdtool plugin: Unknown DS type: %i",
					d->type);
			break;
		}

		if (isnan (d->min))
		{
			strcpy (min, "U");
		}
		else
		{
			snprintf (min, sizeof (min), "%lf", d->min);
			min[sizeof (min) - 1] = '\0';
		}

		if (isnan (d->max))
		{
			strcpy (max, "U");
		}
		else
		{
			snprintf (max, sizeof (max), "%lf", d->max);
			max[sizeof (max) - 1] = '\0';
		}

		status = snprintf (buffer, sizeof (buffer),
				"DS:%s:%s:%i:%s:%s",
				d->name, type,
				(heartbeat > 0) ? heartbeat : (2 * vl->interval),
				min, max);
		if ((status < 1) || (status >= sizeof (buffer)))
			break;

		ds_def[ds_num] = sstrdup (buffer);
	} /* for ds_num = 0 .. ds->ds_num */

#if COLLECT_DEBUG
{
	int i;
	DEBUG ("ds_num = %i", ds_num);
	for (i = 0; i < ds_num; i++)
		DEBUG ("  %s", ds_def[i]);
}
#endif

	if (ds_num != ds->ds_num)
	{
		ds_free (ds_num, ds_def);
		return (-1);
	}

	*ret = ds_def;
	return (ds_num);
}