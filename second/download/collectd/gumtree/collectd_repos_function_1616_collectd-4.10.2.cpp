int plugin_register_read (const char *name,
		int (*callback) (void))
{
	read_func_t *rf;

	rf = (read_func_t *) malloc (sizeof (read_func_t));
	if (rf == NULL)
	{
		char errbuf[1024];
		ERROR ("plugin_register_read: malloc failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
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

	return (plugin_insert_read (rf));
}