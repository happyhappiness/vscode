int plugin_register_complex_read (const char *group, const char *name,
		plugin_read_cb callback,
		const struct timespec *interval,
		user_data_t *user_data)
{
	read_func_t *rf;
	int status;

	rf = malloc (sizeof (*rf));
	if (rf == NULL)
	{
		ERROR ("plugin_register_complex_read: malloc failed.");
		return (ENOMEM);
	}

	memset (rf, 0, sizeof (read_func_t));
	rf->rf_callback = (void *) callback;
	if (group != NULL)
		sstrncpy (rf->rf_group, group, sizeof (rf->rf_group));
	else
		rf->rf_group[0] = '\0';
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

	status = plugin_insert_read (rf);
	if (status != 0)
		sfree (rf);

	return (status);
}