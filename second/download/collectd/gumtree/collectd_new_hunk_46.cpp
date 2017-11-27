 * </Plugin>
 */
static int cf_callback_plugin (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	DEBUG_CALLBACK (shortvar, var, arguments, value);

	if (flags == LC_FLAGS_SECTIONSTART)
	{
		if (nesting_depth != 0)
		{
			fprintf (stderr, ERR_NOT_NESTED);
