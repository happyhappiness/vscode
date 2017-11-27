static int csv_write (const data_set_t *ds, const value_list_t *vl)
{
	struct stat  statbuf;
	char         filename[512];
	char         values[512];
	FILE        *csv;
	int          csv_fd;
	struct flock fl;
	int          status;

	if (0 != strcmp (ds->type, vl->type)) {
		ERROR ("csv plugin: DS type does not match value list type");
		return -1;
	}

	if (value_list_to_filename (filename, sizeof (filename), ds, vl) != 0)
		return (-1);

	DEBUG ("csv plugin: csv_write: filename = %s;", filename);

	if (value_list_to_string (values, sizeof (values), ds, vl) != 0)
		return (-1);

	if (use_stdio)
	{
		size_t i;

		escape_string (filename, sizeof (filename));

		/* Replace commas by colons for PUTVAL compatible output. */
		for (i = 0; i < sizeof (values); i++)
		{
			if (values[i] == 0)
				break;
			else if (values[i] == ',')
				values[i] = ':';
		}

		fprintf (use_stdio == 1 ? stdout : stderr,
			 "PUTVAL %s interval=%i %s\n",
			 filename, interval_g, values);
		return (0);
	}

	if (stat (filename, &statbuf) == -1)
	{
		if (errno == ENOENT)
		{
			if (csv_create_file (filename, ds))
				return (-1);
		}
		else
		{
			char errbuf[1024];
			ERROR ("stat(%s) failed: %s", filename,
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}
	}
	else if (!S_ISREG (statbuf.st_mode))
	{
		ERROR ("stat(%s): Not a regular file!",
				filename);
		return (-1);
	}

	csv = fopen (filename, "a");
	if (csv == NULL)
	{
		char errbuf[1024];
		ERROR ("csv plugin: fopen (%s) failed: %s", filename,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}
	csv_fd = fileno (csv);

	memset (&fl, '\0', sizeof (fl));
	fl.l_start  = 0;
	fl.l_len    = 0; /* till end of file */
	fl.l_pid    = getpid ();
	fl.l_type   = F_WRLCK;
	fl.l_whence = SEEK_SET;

	status = fcntl (csv_fd, F_SETLK, &fl);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR ("csv plugin: flock (%s) failed: %s", filename,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		fclose (csv);
		return (-1);
	}

	fprintf (csv, "%s\n", values);

	/* The lock is implicitely released. I we don't release it explicitely
	 * because the `FILE *' may need to flush a cache first */
	fclose (csv);

	return (0);
}