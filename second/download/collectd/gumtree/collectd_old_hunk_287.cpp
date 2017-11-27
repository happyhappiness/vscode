	if ((*max_ptr == '\0') || (*max_ptr == '~'))
		range->max = NAN;
	else
		range->max = atof (max_ptr);
} /* void parse_range */

int match_range (range_t *range, double value)
{
	int ret = 0;

	if (!isnan (range->min) && (range->min > value))
		ret = 1;
	if (!isnan (range->max) && (range->max < value))
		ret = 1;

	return (((ret - range->invert) == 0) ? 0 : 1);
}

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
} /* int get_values */

static void usage (const char *name)
{
	fprintf (stderr, "Usage: %s <-s socket> <-n value_spec> <-H hostname> [options]\n"
			"\n"
			"Valid options are:\n"
			"  -s <socket>    Path to collectd's UNIX-socket.\n"
			"  -n <v_spec>    Value specification to get from collectd.\n"
			"                 Format: `plugin-instance/type-instance'\n"
			"  -d <ds>        Select the DS to examine. May be repeated to examine multiple\n"
			"                 DSes. By default all DSes are used.\n"
			"  -g <consol>    Method to use to consolidate several DSes.\n"
			"                 Valid arguments are `none', `average' and `sum'\n"
			"  -H <host>      Hostname to query the values for.\n"
			"  -c <range>     Critical range\n"
			"  -w <range>     Warning range\n"
			"\n"
			"Consolidation functions:\n"
			"  none:          Apply the warning- and critical-ranges to each data-source\n"
			"                 individually.\n"
			"  average:       Calculate the average of all matching DSes and apply the\n"
			"                 warning- and critical-ranges to the calculated average.\n"
			"  sum:           Apply the ranges to the sum of all DSes.\n"
			"\n", name);
	exit (1);
} /* void usage */

int do_check_con_none (int values_num, double *values, char **values_names)
{
	int i;

	int num_critical = 0;
	int num_warning  = 0;
	int num_okay = 0;

	for (i = 0; i < values_num; i++)
	{
		if (isnan (values[i]))
			num_warning++;
		else if (match_range (&range_critical_g, values[i]) != 0)
