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
}