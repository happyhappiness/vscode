int cf_callback_mode_switch (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
			shortvar, var, arguments, value);

	if (strcasecmp (shortvar, "Client") == 0)
		operating_mode = MODE_CLIENT;
	else if (strcasecmp (shortvar, "Local") == 0)
		operating_mode = MODE_LOCAL;
	else if (strcasecmp (shortvar, "Server") == 0)
		operating_mode = MODE_SERVER;
	else
	{
		fprintf (stderr, "cf_callback_mode_switch: Wrong mode!\n");
		return (LC_CBRET_ERROR);
	}

	return (LC_CBRET_OKAY);
}