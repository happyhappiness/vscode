void plugin_read_all (const int *loop)
{
	llentry_t   *le;
	read_func_t *rf;

	if (list_read == NULL)
		return;

	pthread_mutex_lock (&read_lock);

	le = llist_head (list_read);
	while (le != NULL)
	{
		rf = (read_func_t *) le->value;

		if (rf->needs_read != DONE)
		{
			le = le->next;
			continue;
		}

		if (rf->wait_left > 0)
			rf->wait_left -= interval_g;

		if (rf->wait_left <= 0)
		{
			rf->needs_read = TODO;
		}

		le = le->next;
	}

	DEBUG ("plugin: plugin_read_all: Signalling `read_cond'");
	pthread_cond_broadcast (&read_cond);
	pthread_mutex_unlock (&read_lock);
}