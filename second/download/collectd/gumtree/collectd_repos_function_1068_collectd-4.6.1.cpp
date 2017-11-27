int plugin_read_all_once (void)
{
	llentry_t   *le;
	read_func_t *rf;
	int status;
	int return_status = 0;

	if (list_read == NULL)
	{
		NOTICE ("No read-functions are registered.");
		return (0);
	}

	for (le = llist_head (list_read);
	     le != NULL;
	     le = le->next)
	{
		rf = (read_func_t *) le->value;
		status = rf->callback ();
		if (status != 0)
		{
			NOTICE ("read-function of plugin `%s' failed.",
				le->key);
			return_status = -1;
		}
	}

	return (return_status);
}