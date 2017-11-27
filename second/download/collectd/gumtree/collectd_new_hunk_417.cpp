	printf ("%s: %lf percent |", status_str, percentage);
	for (i = 0; i < values_num; i++)
		printf (" %s=%lf;;;;", values_names[i], values[i]);
	return (status_code);
} /* int do_check_con_percentage */

static int do_check (lcc_connection_t *connection)
{
	gauge_t *values;
	char   **values_names;
	size_t   values_num;
	char ident_str[1024];
	lcc_identifier_t ident;
	size_t i;
	int status;

	snprintf (ident_str, sizeof (ident_str), "%s/%s",
			hostname_g, value_string_g);
	ident_str[sizeof (ident_str) - 1] = 0;

	memset (&ident, 0, sizeof (ident));
	status = lcc_string_to_identifier (connection, &ident, ident_str);
	if (status != 0)
	{
		printf ("ERROR: Creating an identifier failed: %s.\n",
				lcc_strerror (connection));
