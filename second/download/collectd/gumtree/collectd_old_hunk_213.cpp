		fprintf (stderr, "fgets failed: %s\n",
				strerror (errno));
		fclose (fh_in);
		fclose (fh_out);
		return (-1);
	}
	fclose (fh_in); fh_in = NULL; fd = -1;
	fclose (fh_out); fh_out = NULL;

	values_num = atoi (buffer);
	if (values_num < 1)
		return (-1);

	values = (double *) malloc (values_num * sizeof (double));
	if (values == NULL)
	{
		fprintf (stderr, "malloc failed: %s\n",
				strerror (errno));
