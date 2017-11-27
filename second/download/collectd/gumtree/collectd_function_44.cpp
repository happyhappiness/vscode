static int log_create_file (char *filename, char **ds_def, int ds_num)
{
	FILE *log;
	int i;

	if (check_create_dir (filename))
		return (-1);

	log = fopen (filename, "w");
	if (log == NULL)
	{
		syslog (LOG_WARNING, "Failed to create %s: %s", filename,
				strerror(errno));
		return (-1);
	}

	fprintf (log, "epoch");
	for (i = 0; i < ds_num; i++)
	{
		char *name;
		char *tmp;

		name = strchr (ds_def[i], ':');
		if (name == NULL)
		{
			syslog (LOG_WARNING, "Invalid DS definition '%s' for %s",
					ds_def[i], filename);
			fclose(log);
			remove(filename);
			return (-1);
		}

		name += 1;
		tmp = strchr (name, ':');
		if (tmp == NULL)
		{
			syslog (LOG_WARNING, "Invalid DS definition '%s' for %s",
					ds_def[i], filename);
			fclose(log);
			remove(filename);
			return (-1);
		}

		/* The `%.*s' is needed because there is no null-byte behind
		 * the name. */
		fprintf(log, ",%.*s", (tmp - name), name);
	}
	fprintf(log, "\n");
	fclose(log);

	return 0;
}