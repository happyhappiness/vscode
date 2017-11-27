int plugin_register_complex_read (const char *name,
		plugin_read_cb callback,
		const struct timespec *interval,
		user_data_t *user_data)
{
	read_func_t *rf;

	rf = (read_func_t *) malloc (sizeof (read_func_t));
	if (rf == NULL)
	{
		ERROR ("plugin_register_complex_read: malloc failed.");
		return (-1);
	}

	memset (rf, 0, sizeof (read_func_t));
	rf->rf_callback = (void *) callback;
	sstrncpy (rf->rf_name, name, sizeof (rf->rf_name));
	rf->rf_type = RF_COMPLEX;
	if (interval != NULL)
	{
		rf->rf_interval = *interval;
	}
	rf->rf_effective_interval = rf->rf_interval;

	/* Set user data */
	if (user_data == NULL)
	{
		rf->rf_udata.data = NULL;
		rf->rf_udata.free_func = NULL;
	}
	else
	{
		rf->rf_udata = *user_data;
	}

	return (plugin_insert_read (rf));
}