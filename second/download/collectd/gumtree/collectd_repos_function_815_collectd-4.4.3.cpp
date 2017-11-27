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

	memset (rf, '\0', sizeof (read_func_t));
	rf->wait_time = interval_g;
	rf->wait_left = 0;
	rf->callback = callback;
	rf->needs_read = DONE;

	return (register_callback (&list_read, name, (void *) rf));
}