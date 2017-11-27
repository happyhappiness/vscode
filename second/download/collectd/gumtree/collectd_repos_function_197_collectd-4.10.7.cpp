static int apache_read_host (user_data_t *user_data) /* {{{ */
{
	int i;

	char *ptr;
	char *saveptr;
	char *lines[16];
	int   lines_num = 0;

	char *fields[4];
	int   fields_num;

	apache_t *st;

	st = user_data->data;

	assert (st->url != NULL);
	/* (Assured by `config_add') */

	if (st->curl == NULL)
	{
		int status;

		status = init_host (st);
		if (status != 0)
			return (-1);
	}
	assert (st->curl != NULL);

	st->apache_buffer_fill = 0;
	if (curl_easy_perform (st->curl) != 0)
	{
		ERROR ("apache: curl_easy_perform failed: %s",
				st->apache_curl_error);
		return (-1);
	}

	/* fallback - server_type to apache if not set at this time */
	if (st->server_type == -1)
	{
		WARNING ("apache plugin: Unable to determine server software "
				"automatically. Will assume Apache.");
		st->server_type = APACHE;
	}

	ptr = st->apache_buffer;
	saveptr = NULL;
	while ((lines[lines_num] = strtok_r (ptr, "\n\r", &saveptr)) != NULL)
	{
		ptr = NULL;
		lines_num++;

		if (lines_num >= 16)
			break;
	}

	for (i = 0; i < lines_num; i++)
	{
		fields_num = strsplit (lines[i], fields, 4);

		if (fields_num == 3)
		{
			if ((strcmp (fields[0], "Total") == 0)
					&& (strcmp (fields[1], "Accesses:") == 0))
				submit_counter ("apache_requests", "",
						atoll (fields[2]), st);
			else if ((strcmp (fields[0], "Total") == 0)
					&& (strcmp (fields[1], "kBytes:") == 0))
				submit_counter ("apache_bytes", "",
						1024LL * atoll (fields[2]), st);
		}
		else if (fields_num == 2)
		{
			if (strcmp (fields[0], "Scoreboard:") == 0)
				submit_scoreboard (fields[1], st);
			else if ((strcmp (fields[0], "BusyServers:") == 0) /* Apache 1.* */
					|| (strcmp (fields[0], "BusyWorkers:") == 0) /* Apache 2.* */)
				submit_gauge ("apache_connections", NULL, atol (fields[1]), st);
			else if ((strcmp (fields[0], "IdleServers:") == 0) /* Apache 1.x */
					|| (strcmp (fields[0], "IdleWorkers:") == 0) /* Apache 2.x */)
				submit_gauge ("apache_idle_workers", NULL, atol (fields[1]), st);
		}
	}

	st->apache_buffer_fill = 0;

	return (0);
}