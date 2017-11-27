static int value_list_to_filename (char *buffer, int buffer_len,
		const data_set_t *ds, const value_list_t *vl)
{
	int offset = 0;
	int status;

	assert (0 == strcmp (ds->type, vl->type));

	if (datadir != NULL)
	{
		status = ssnprintf (buffer + offset, buffer_len - offset,
				"%s/", datadir);
		if ((status < 1) || (status >= buffer_len - offset))
			return (-1);
		offset += status;
	}

	status = ssnprintf (buffer + offset, buffer_len - offset,
			"%s/", vl->host);
	if ((status < 1) || (status >= buffer_len - offset))
		return (-1);
	offset += status;

	if (strlen (vl->plugin_instance) > 0)
		status = ssnprintf (buffer + offset, buffer_len - offset,
				"%s-%s/", vl->plugin, vl->plugin_instance);
	else
		status = ssnprintf (buffer + offset, buffer_len - offset,
				"%s/", vl->plugin);
	if ((status < 1) || (status >= buffer_len - offset))
		return (-1);
	offset += status;

	if (strlen (vl->type_instance) > 0)
		status = ssnprintf (buffer + offset, buffer_len - offset,
				"%s-%s", vl->type, vl->type_instance);
	else
		status = ssnprintf (buffer + offset, buffer_len - offset,
				"%s", vl->type);
	if ((status < 1) || (status >= buffer_len - offset))
		return (-1);
	offset += status;

	if (!use_stdio)
	{
		time_t now;
		struct tm stm;

		/* TODO: Find a way to minimize the calls to `localtime_r',
		 * since they are pretty expensive.. */
		now = time (NULL);
		if (localtime_r (&now, &stm) == NULL)
		{
			ERROR ("csv plugin: localtime_r failed");
			return (1);
		}

		strftime (buffer + offset, buffer_len - offset,
				"-%Y-%m-%d", &stm);
	}

	return (0);
}