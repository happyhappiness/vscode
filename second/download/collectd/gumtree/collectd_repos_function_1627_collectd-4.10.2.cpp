int plugin_unregister_read (const char *name) /* {{{ */
{
	llentry_t *le;
	read_func_t *rf;

	if (name == NULL)
		return (-ENOENT);

	pthread_mutex_lock (&read_lock);

	if (read_list == NULL)
	{
		pthread_mutex_unlock (&read_lock);
		return (-ENOENT);
	}

	le = llist_search (read_list, name);
	if (le == NULL)
	{
		pthread_mutex_unlock (&read_lock);
		WARNING ("plugin_unregister_read: No such read function: %s",
				name);
		return (-ENOENT);
	}

	llist_remove (read_list, le);

	rf = le->value;
	assert (rf != NULL);
	rf->rf_type = RF_REMOVE;

	pthread_mutex_unlock (&read_lock);

	llentry_destroy (le);

	DEBUG ("plugin_unregister_read: Marked `%s' for removal.", name);

	return (0);
}