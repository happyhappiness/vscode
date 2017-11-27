		printf ("WARNING: No defined values found\n");
		return (RET_WARNING);
	}

	if (match_range (&range_critical_g, total) != 0)
	{
		status_str = "CRITICAL";
		status_code = RET_CRITICAL;
	}
	else if (match_range (&range_warning_g, total) != 0)
	{
		status_str = "WARNING";
		status_code = RET_WARNING;
	}
	else
	{
		status_str = "OKAY";
		status_code = RET_OKAY;
	}

	printf ("%s: %g sum |", status_str, total);
	for (i = 0; i < values_num; i++)
		printf (" %s=%g;;;;", values_names[i], values[i]);
	printf ("\n");

	return (status_code);
} /* int do_check_con_sum */

static int do_check_con_percentage (size_t values_num,
		double *values, char **values_names)
{
	size_t i;
	double sum = 0.0;
	double percentage;

	const char *status_str  = "UNKNOWN";
	int         status_code = RET_UNKNOWN;

	if ((values_num < 1) || (isnan (values[0])))
	{
		printf ("WARNING: The first value is not defined\n");
		return (RET_WARNING);
	}

	for (i = 0; i < values_num; i++)
		if (!isnan (values[i]))
			sum += values[i];

	if (sum == 0.0)
	{
		printf ("WARNING: Values sum up to zero\n");
		return (RET_WARNING);
	}

	percentage = 100.0 * values[0] / sum;

	if (match_range (&range_critical_g, percentage) != 0)
	{
		status_str  = "CRITICAL";
		status_code = RET_CRITICAL;
	}
	else if (match_range (&range_warning_g, percentage) != 0)
	{
		status_str  = "WARNING";
		status_code = RET_WARNING;
	}
	else
	{
		status_str  = "OKAY";
		status_code = RET_OKAY;
	}

	printf ("%s: %lf percent |", status_str, percentage);
	for (i = 0; i < values_num; i++)
		printf (" %s=%lf;;;;", values_names[i], values[i]);
	return (status_code);
} /* int do_check_con_percentage */

static int do_check (void)
{
	lcc_connection_t *connection;
	gauge_t *values;
	char   **values_names;
	size_t   values_num;
	char address[1024];
	char ident_str[1024];
	lcc_identifier_t ident;
	size_t i;
	int status;

	snprintf (address, sizeof (address), "unix:%s", socket_file_g);
	address[sizeof (address) - 1] = 0;

	snprintf (ident_str, sizeof (ident_str), "%s/%s",
			hostname_g, value_string_g);
	ident_str[sizeof (ident_str) - 1] = 0;

	connection = NULL;
	status = lcc_connect (address, &connection);
	if (status != 0)
	{
		printf ("ERROR: Connecting to daemon at %s failed.\n",
				socket_file_g);
		return (RET_CRITICAL);
	}

	memset (&ident, 0, sizeof (ident));
	status = lcc_string_to_identifier (connection, &ident, ident_str);
	if (status != 0)
	{
		printf ("ERROR: Creating an identifier failed: %s.\n",
				lcc_strerror (connection));
		LCC_DESTROY (connection);
		return (RET_CRITICAL);
	}

	status = lcc_getval (connection, &ident,
			&values_num, &values, &values_names);
	if (status != 0)
	{
		printf ("ERROR: Retrieving values from the daemon failed: %s.\n",
				lcc_strerror (connection));
		LCC_DESTROY (connection);
		return (RET_CRITICAL);
	}

	LCC_DESTROY (connection);

	status = filter_ds (&values_num, &values, &values_names);
	if (status != RET_OKAY)
		return (status);

	status = RET_UNKNOWN;
	if (consolitation_g == CON_NONE)
		status =  do_check_con_none (values_num, values, values_names);
	else if (consolitation_g == CON_AVERAGE)
		status =  do_check_con_average (values_num, values, values_names);
	else if (consolitation_g == CON_SUM)
		status = do_check_con_sum (values_num, values, values_names);
	else if (consolitation_g == CON_PERCENTAGE)
		status = do_check_con_percentage (values_num, values, values_names);

	free (values);
	if (values_names != NULL)
		for (i = 0; i < values_num; i++)
			free (values_names[i]);
	free (values_names);

	return (status);
} /* int do_check */

int main (int argc, char **argv)
{
	range_critical_g.min = NAN;
	range_critical_g.max = NAN;
	range_critical_g.invert = 0;
