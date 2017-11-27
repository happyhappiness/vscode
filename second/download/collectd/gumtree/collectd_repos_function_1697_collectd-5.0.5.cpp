int plugin_register_read (const char *name,
		int (*callback) (void))
{
	read_func_t *rf;
	int status;

	rf = malloc (sizeof (*rf));
	if (rf == NULL)
	{
		ERROR ("plugin_register_read: malloc failed.");
		return (ENOMEM);
	}

	memset (rf, 0, sizeof (read_func_t));
	rf->rf_callback = (void *) callback;
	rf->rf_udata.data = NULL;
	rf->rf_udata.free_func = NULL;
	rf->rf_group[0] = '\0';
	sstrncpy (rf->rf_name, name, sizeof (rf->rf_name));
	rf->rf_type = RF_SIMPLE;
	rf->rf_interval.tv_sec = 0;
	rf->rf_interval.tv_nsec = 0;
	rf->rf_effective_interval = rf->rf_interval;

	status = plugin_insert_read (rf);
	if (status != 0)
		sfree (rf);

	return (status);
}