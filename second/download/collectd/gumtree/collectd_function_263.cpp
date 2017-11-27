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
	int j;

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
	memset (values_names, 0, values_num * sizeof (char *));

	i = 0; /* index of the values returned by the server */
	j = 0; /* number of values in `values_names' and `values' */
	while (fgets (buffer, sizeof (buffer), fh_in) != NULL)
	{
		do /* while (0) */
		{
			char *key;
			char *value;
			char *endptr;

			key = buffer;

			value = strchr (key, '=');
			if (value == NULL)
			{
				fprintf (stderr, "Cannot parse line: %s\n", buffer);
				break;
			}
			*value = 0;
			value++;

			if (ignore_ds (key) != 0)
				break;

			endptr = NULL;
			errno = 0;
			values[j] = strtod (value, &endptr);
			if ((endptr == value) || (errno != 0))
			{
				fprintf (stderr, "Could not parse buffer "
						"as number: %s\n", value);
				break;
			}

			values_names[j] = strdup (key);
			if (values_names[j] == NULL)
			{
				fprintf (stderr, "strdup failed.\n");
				break;
			}
			j++;
		} while (0);

		i++;
		if (i >= values_num)
			break;
	}
	/* Set `values_num' to the number of values actually stored in the
	 * array. */
	values_num = j;

	fclose (fh_in); fh_in = NULL; fd = -1;
	fclose (fh_out); fh_out = NULL;

	*ret_values_num = values_num;
	*ret_values = values;
	*ret_values_names = values_names;

	return (0);
}