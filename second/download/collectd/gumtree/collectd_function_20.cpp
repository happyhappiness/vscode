static int cf_callback_mode (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	DEBUG_CALLBACK (shortvar, var, arguments, value);

	if (strcasecmp (value, "Client") == 0)
		operating_mode = MODE_CLIENT;
#if HAVE_LIBRRD
	else if (strcasecmp (value, "Server") == 0)
		operating_mode = MODE_SERVER;
	else if (strcasecmp (value, "Local") == 0)
		operating_mode = MODE_LOCAL;
#else /* !HAVE_LIBRRD */
	else if (strcasecmp (value, "Server") == 0)
	{
		fprintf (stderr, "Invalid mode `Server': "
				"You need to link against librrd for this "
				"mode to be available.\n");
		syslog (LOG_ERR, "Invalid mode `Server': "
				"You need to link against librrd for this "
				"mode to be available.");
		return (LC_CBRET_ERROR);
	}
	else if (strcasecmp (value, "Local") == 0)
	{
		fprintf (stderr, "Invalid mode `Local': "
				"You need to link against librrd for this "
				"mode to be available.\n");
		syslog (LOG_ERR, "Invalid mode `Local': "
				"You need to link against librrd for this "
				"mode to be available.");
		return (LC_CBRET_ERROR);
	}
#endif
	else if (strcasecmp (value, "Log") == 0)
		operating_mode = MODE_LOG;
	else
	{
		syslog (LOG_ERR, "Invalid value for config option `Mode': `%s'", value);
		return (LC_CBRET_ERROR);
	}

	return (LC_CBRET_OKAY);
}