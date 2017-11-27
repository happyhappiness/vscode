
	/* Return `okay' even if there was an error, because it's not a syntax
	 * problem.. */
	return (LC_CBRET_OKAY);
}

static int cf_callback_socket (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	char *buffer;

	char *fields[3];
	int   numfields;

	char *node;
	char *service = NET_DEFAULT_PORT;

	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
			shortvar, var, arguments, value);

	buffer = strdup (value);
	if (buffer == NULL)
		return (LC_CBRET_ERROR);

	numfields = strsplit (buffer, fields, 3);

	if ((numfields != 1) && (numfields != 2))
	{
		syslog (LOG_ERR, "Invalid number of arguments to `%s'",
				shortvar);
		free (buffer);
		return (LC_CBRET_ERROR);
	}

	node = fields[0];
	if (numfields == 2)
		service = fields[1];

	/* Still return `LC_CBRET_OKAY' because this is not an syntax error */
	if (network_create_socket (node, service) < 1)
		syslog (LOG_ERR, "network_create_socket (%s, %s) failed",
				node, service);

	free (buffer);

	return (LC_CBRET_OKAY);
}

/*
 * `cf_callback_plugin'
 *   Start/end section `plugin'
 *
 * <Plugin `arguments'>
 *   ...
 * </Plugin>
 */
static int cf_callback_plugin (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
			shortvar, var, arguments, value);

