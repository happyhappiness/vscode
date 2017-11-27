 * </Mode>
 */
static int cf_callback_mode_plugindir (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
			shortvar, var, arguments, value);

	plugin_set_dir (value);

	return (LC_CBRET_OKAY);
}

static int cf_callback_mode_option (const char *shortvar, const char *var,
		const char *arguments, const char *value, lc_flags_t flags,
		void *extra)
{
	cf_mode_item_t *item;

	DBG ("shortvar = %s, var = %s, arguments = %s, value = %s, ...",
			shortvar, var, arguments, value);

	if (extra == NULL)
	{
		fprintf (stderr, "No extra..?\n");
		return (LC_CBRET_ERROR);
	}
