static int apache_read (void)
{
	int i;

	char *ptr;
	char *saveptr;
	char *lines[16];
	int   lines_num = 0;

	char *fields[4];
	int   fields_num;

	if (curl == NULL)
		return (-1);
	if (url == NULL)
		return (-1);

	apache_buffer_fill = 0;
	if (curl_easy_perform (curl) != 0)
	{
		ERROR ("apache: curl_easy_perform failed: %s",
				apache_curl_error);
		return (-1);
	}

	ptr = apache_buffer;
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
						atoll (fields[2]));
			else if ((strcmp (fields[0], "Total") == 0)
					&& (strcmp (fields[1], "kBytes:") == 0))
				submit_counter ("apache_bytes", "",
						1024LL * atoll (fields[2]));
		}
		else if (fields_num == 2)
		{
			if (strcmp (fields[0], "Scoreboard:") == 0)
				submit_scoreboard (fields[1]);
			else if (strcmp (fields[0], "BusyServers:") == 0)
				submit_gauge ("apache_connections", NULL, atol (fields[1]));
		}
	}

	apache_buffer_fill = 0;

	return (0);
}