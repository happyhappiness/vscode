static void *us_handle_client (void *arg)
{
	int fd;
	FILE *fh;
	char buffer[1024];
	char *fields[128];
	int   fields_num;

	fd = *((int *) arg);
	free (arg);
	arg = NULL;

	DEBUG ("Reading from fd #%i", fd);

	fh = fdopen (fd, "r+");
	if (fh == NULL)
	{
		char errbuf[1024];
		ERROR ("unixsock plugin: fdopen failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		close (fd);
		pthread_exit ((void *) 1);
	}

	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		int len;

		len = strlen (buffer);
		while ((len > 0)
				&& ((buffer[len - 1] == '\n') || (buffer[len - 1] == '\r')))
			buffer[--len] = '\0';

		if (len == 0)
			continue;

		DEBUG ("fgets -> buffer = %s; len = %i;", buffer, len);

		fields_num = strsplit (buffer, fields,
				sizeof (fields) / sizeof (fields[0]));

		if (fields_num < 1)
		{
			close (fd);
			break;
		}

		if (strcasecmp (fields[0], "getval") == 0)
		{
			us_handle_getval (fh, fields, fields_num);
		}
		else if (strcasecmp (fields[0], "putval") == 0)
		{
			us_handle_putval (fh, fields, fields_num);
		}
		else
		{
			fprintf (fh, "-1 Unknown command: %s\n", fields[0]);
			fflush (fh);
		}
	} /* while (fgets) */

	DEBUG ("Exiting..");
	close (fd);

	pthread_exit ((void *) 0);
}