int plugin_register_read (const char *name,
		int (*callback) (void))
{
	read_func_t *rf;
	int status;

	rf = calloc (1, sizeof (*rf));
	if (rf == NULL)
	{
		ERROR ("plugin_register_read: calloc failed.");
		return (ENOMEM);
	}

	rf->rf_callback = (void *) callback;
	rf->rf_udata.data = NULL;
	rf->rf_udata.free_func = NULL;
	rf->rf_ctx = plugin_get_ctx ();
	rf->rf_group[0] = '\0';
	rf->rf_name = strdup (name);
	rf->rf_type = RF_SIMPLE;
	rf->rf_interval = plugin_get_interval ();

	status = plugin_insert_read (rf);
	if (status != 0) {
		sfree (rf->rf_name);
		sfree (rf);
	}

	return (status);
}