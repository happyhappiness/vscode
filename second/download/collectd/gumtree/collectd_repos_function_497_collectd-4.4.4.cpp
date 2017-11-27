static void logfile_print (const char *msg, time_t timestamp_time)
{
	FILE *fh;
	int do_close = 0;
	struct tm timestamp_tm;
	char timestamp_str[64];

	if (print_timestamp)
	{
		localtime_r (&timestamp_time, &timestamp_tm);

		strftime (timestamp_str, sizeof (timestamp_str), "%Y-%m-%d %H:%M:%S",
				&timestamp_tm);
		timestamp_str[sizeof (timestamp_str) - 1] = '\0';
	}

	pthread_mutex_lock (&file_lock);

	if (log_file == NULL)
	{
		fh = fopen (DEFAULT_LOGFILE, "a");
		do_close = 1;
	}
	else if (strcasecmp (log_file, "stderr") == 0)
		fh = stderr;
	else if (strcasecmp (log_file, "stdout") == 0)
		fh = stdout;
	else
	{
		fh = fopen (log_file, "a");
		do_close = 1;
	}

	if (fh == NULL)
	{
			char errbuf[1024];
			fprintf (stderr, "logfile plugin: fopen (%s) failed: %s\n",
					(log_file == NULL) ? DEFAULT_LOGFILE : log_file,
					sstrerror (errno, errbuf, sizeof (errbuf)));
	}
	else
	{
		if (print_timestamp)
			fprintf (fh, "[%s] %s\n", timestamp_str, msg);
		else
			fprintf (fh, "%s\n", msg);

		if (do_close != 0)
			fclose (fh);
	}

	pthread_mutex_unlock (&file_lock);

	return;
}