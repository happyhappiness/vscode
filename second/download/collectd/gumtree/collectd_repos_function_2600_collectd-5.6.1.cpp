int plugin_register_complex_read (const char *group, const char *name,
		plugin_read_cb callback,
		cdtime_t interval,
		user_data_t const *user_data)
{
	read_func_t *rf;
	int status;

	rf = calloc (1,sizeof (*rf));
	if (rf == NULL)
	{
		ERROR ("plugin_register_complex_read: calloc failed.");
		return (ENOMEM);
	}

	rf->rf_callback = (void *) callback;
	if (group != NULL)
		sstrncpy (rf->rf_group, group, sizeof (rf->rf_group));
	else
		rf->rf_group[0] = '\0';
	rf->rf_name = strdup (name);
	rf->rf_type = RF_COMPLEX;
	rf->rf_interval = (interval != 0) ? interval : plugin_get_interval ();

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

	rf->rf_ctx = plugin_get_ctx ();

	status = plugin_insert_read (rf);
	if (status != 0) {
		sfree (rf->rf_name);
		sfree (rf);
	}

	return (status);
}