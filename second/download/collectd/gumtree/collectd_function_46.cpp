static int log_update_file (char *host, char *file, char *values,
		char **ds_def, int ds_num)
{
	char *tmp;
	FILE *fp;
	struct stat statbuf;
	char full_file[1024];

	/* Cook the values a bit: Substitute colons with commas */
	strsubstitute (values, ':', ',');

	/* host == NULL => local mode */
	if (host != NULL)
	{
		if (snprintf (full_file, 1024, "%s/%s", host, file) >= 1024)
			return (-1);
	}
	else
	{
		if (snprintf (full_file, 1024, "%s", file) >= 1024)
			return (-1);
	}

	strncpy (full_file, file, 1024);

	tmp = full_file + strlen (full_file) - 4;
	assert (tmp > 0);

	/* Change the filename for logfiles. */
	if (strncmp (tmp, ".rrd", 4) == 0)
	{
		time_t now;
		struct tm *tm;

		/* TODO: Find a way to minimize the calls to `localtime', since
		 * they are pretty expensive.. */
		now = time (NULL);
		tm = localtime (&now);

		strftime (tmp, 1024 - (tmp - full_file), "-%Y-%m-%d", tm);

		/* `localtime(3)' returns a pointer to static data,
		 * therefore the pointer may not be free'd. */
	}
	else
		DBG ("The filename ends with `%s' which is unexpected.", tmp);

	if (stat (full_file, &statbuf) == -1)
	{
		if (errno == ENOENT)
		{
			if (log_create_file (full_file, ds_def, ds_num))
				return (-1);
		}
		else
		{
			syslog (LOG_ERR, "stat %s: %s", full_file, strerror (errno));
			return (-1);
		}
	}
	else if (!S_ISREG (statbuf.st_mode))
	{
		syslog (LOG_ERR, "stat %s: Not a regular file!", full_file);
		return (-1);
	}


	fp = fopen (full_file, "a");
	if (fp == NULL)
	{
		syslog (LOG_WARNING, "Failed to append to %s: %s", full_file,
				strerror(errno));
		return (-1);
	}
	fprintf(fp, "%s\n", values);
	fclose(fp);

	return (0);
}