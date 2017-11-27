static void logfile_log (int severity, const char *msg)
{
	FILE *fh;
	int do_close = 0;

	if (severity > log_level)
		return;

	pthread_mutex_lock (&file_lock);

	if ((log_file == NULL) || (strcasecmp (log_file, "stderr") == 0))
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
					(log_file == NULL) ? "<null>" : log_file,
					sstrerror (errno, errbuf, sizeof (errbuf)));
	}
	else
	{
		fprintf (fh, "%s\n", msg);
		if (do_close != 0)
			fclose (fh);
	}

	pthread_mutex_unlock (&file_lock);

	return;
}