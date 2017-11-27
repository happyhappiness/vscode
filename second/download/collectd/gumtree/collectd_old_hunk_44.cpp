 * Mode `value'
 */
static int cf_callback_mode (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
			shortvar, var, arguments, value);

	if (strcasecmp (value, "Client") == 0)
		operating_mode = MODE_CLIENT;
#if HAVE_LIBRRD
	else if (strcasecmp (value, "Server") == 0)
		operating_mode = MODE_SERVER;
	else if (strcasecmp (value, "Local") == 0)
		operating_mode = MODE_LOCAL;
#endif
	else if (strcasecmp (value, "Log") == 0)
		operating_mode = MODE_LOG;
	else
	{
		syslog (LOG_ERR, "Invalid value for config option `Mode': `%s'", value);
