static void *us_handle_client (void *arg)
{
	int fd;
	FILE *fhin, *fhout;
	char buffer[1024];
	char *fields[128];
	int   fields_num;

	fd = *((int *) arg);
	free (arg);
	arg = NULL;

	DEBUG ("Reading from fd #%i", fd);

	fhin  = fdopen (fd, "r");
	if (fhin == NULL)
	{
		char errbuf[1024];
		ERROR ("unixsock plugin: fdopen failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		close (fd);
		pthread_exit ((void *) 1);
	}

	fhout = fdopen (fd, "w");
	if (fhout == NULL)
	{
		char errbuf[1024];
		ERROR ("unixsock plugin: fdopen failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		fclose (fhin); /* this closes fd as well */
		pthread_exit ((void *) 1);
	}

	/* change output buffer to line buffered mode */
	if (setvbuf (fhout, NULL, _IOLBF, 0) != 0)
	{
		char errbuf[1024];
		ERROR ("unixsock plugin: setvbuf failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		fclose (fhin);
		fclose (fhout);
		pthread_exit ((void *) 1);
	}

	while (42)
	{
		int len;

		errno = 0;
		if (fgets (buffer, sizeof (buffer), fhin) == NULL)
		{
			if (errno != 0)
			{
				char errbuf[1024];
				WARNING ("unixsock plugin: failed to read from socket #%i: %s",
						fileno (fhin),
						sstrerror (errno, errbuf, sizeof (errbuf)));
			}
			break;
		}

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
			handle_getval (fhout, fields, fields_num);
		}
		else if (strcasecmp (fields[0], "putval") == 0)
		{
			handle_putval (fhout, fields, fields_num);
		}
		else if (strcasecmp (fields[0], "listval") == 0)
		{
			handle_listval (fhout, fields, fields_num);
		}
		else if (strcasecmp (fields[0], "putnotif") == 0)
		{
			handle_putnotif (fhout, fields, fields_num);
		}
		else if (strcasecmp (fields[0], "flush") == 0)
		{
			handle_flush (fhout, fields, fields_num);
		}
		else
		{
			if (fprintf (fhout, "-1 Unknown command: %s\n", fields[0]) < 0)
			{
				char errbuf[1024];
				WARNING ("unixsock plugin: failed to write to socket #%i: %s",
						fileno (fhout),
						sstrerror (errno, errbuf, sizeof (errbuf)));
				break;
			}
		}
	} /* while (fgets) */

	DEBUG ("Exiting..");
	fclose (fhin);
	fclose (fhout);

	pthread_exit ((void *) 0);
	return ((void *) 0);
}