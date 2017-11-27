	{
		fprintf (stderr, "connect failed: %s\n",
				strerror (errno));
		return (-1);
	}

	fh = fdopen (fd, "r+");
	if (fh == NULL)
	{
		fprintf (stderr, "fdopen failed: %s\n",
				strerror (errno));
		close (fd);
		return (-1);
	}

	fprintf (fh, "GETVAL %s/%s\n", hostname_g, value_string_g);
	fflush (fh);

	if (fgets (buffer, sizeof (buffer), fh) == NULL)
	{
		fprintf (stderr, "fgets failed: %s\n",
				strerror (errno));
		close (fd);
		return (-1);
	}
	close (fd); fd = -1;

	values_num = atoi (buffer);
	if (values_num < 1)
		return (-1);

	values = (double *) malloc (values_num * sizeof (double));
