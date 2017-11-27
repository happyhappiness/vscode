static int get_values (int *ret_values_num, double **ret_values,
		char ***ret_values_names)
{
	struct sockaddr_un sa;
	int status;
	int fd;
	FILE *fh_in, *fh_out;
	char buffer[4096];

	int values_num;
	double *values;
	char **values_names;

	int i;

	fd = socket (PF_UNIX, SOCK_STREAM, 0);
	if (fd < 0)
	{
		fprintf (stderr, "socket failed: %s\n",
				strerror (errno));
		return (-1);
	}

	memset (&sa, '\0', sizeof (sa));
	sa.sun_family = AF_UNIX;
	strncpy (sa.sun_path, socket_file_g,
			sizeof (sa.sun_path) - 1);

	status = connect (fd, (struct sockaddr *) &sa, sizeof (sa));
	if (status != 0)
	{
		fprintf (stderr, "connect failed: %s\n",
				strerror (errno));
		return (-1);
	}

	fh_in = fdopen (fd, "r");
	if (fh_in == NULL)
	{
		fprintf (stderr, "fdopen failed: %s\n",
				strerror (errno));
		close (fd);
		return (-1);
	}

	fh_out = fdopen (fd, "w");
	if (fh_out == NULL)
	{
		fprintf (stderr, "fdopen failed: %s\n",
				strerror (errno));
		fclose (fh_in);
		return (-1);
	}

	fprintf (fh_out, "GETVAL %s/%s\n", hostname_g, value_string_g);
	fflush (fh_out);

	if (fgets (buffer, sizeof (buffer), fh_in) == NULL)
	{
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
		return (-1);
	}

	values_names = (char **) malloc (values_num * sizeof (char *));
	if (values_names == NULL)
	{
		fprintf (stderr, "malloc failed: %s\n",
				strerror (errno));
		free (values);
		return (-1);
	}

	i = 0;
	while (fgets (buffer, sizeof (buffer), fh_in) != NULL)
	{
		char *key;
		char *value;

		key = buffer;

		value = strchr (key, '=');
		if (value == NULL)
			continue;
		*value = '\0'; value++;

		if (ignore_ds (key) != 0)
			continue;

		values_names[i] = strdup (key);
		values[i] = atof (value);

		i++;
		if (i >= values_num)
			break;
	}
	values_num = i;

	fclose (fh_in); fh_in = NULL; fd = -1;
	fclose (fh_out); fh_out = NULL;

	*ret_values_num = values_num;
	*ret_values = values;
	*ret_values_names = values_names;

	return (0);
}