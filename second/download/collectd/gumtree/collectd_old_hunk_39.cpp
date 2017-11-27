
	/* Return `okay' even if there was an error, because it's not a syntax
	 * problem.. */
	return (LC_CBRET_OKAY);
}

/*
 * `cf_callback_mode_switch'
 *   Change the contents of the global variable `operating_mode'
 *
 *   This should be command line options. One *can* do this in the config
 *   files, but I will not document this. Don't whine abount it not working as
 *   you expect if you do it anyways.
 */
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

/*
 * `cf_callback_plugin'
 *   Start/end section `plugin'
 *
 * <Plugin `arguments'>
 *   ...
 * </Plugin>
 */
int cf_callback_plugin (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
			shortvar, var, arguments, value);

