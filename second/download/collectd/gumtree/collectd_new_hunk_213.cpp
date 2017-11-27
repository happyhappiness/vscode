		fprintf (stderr, "fgets failed: %s\n",
				strerror (errno));
		fclose (fh_in);
		fclose (fh_out);
		return (-1);
	}

	{
		char *ptr = strchr (buffer, ' ');

		if (ptr != NULL)
			*ptr = '\0';

		values_num = atoi (buffer);
		if (values_num < 1)
			return (-1);
	}

	values = (double *) malloc (values_num * sizeof (double));
	if (values == NULL)
	{
		fprintf (stderr, "malloc failed: %s\n",
				strerror (errno));
