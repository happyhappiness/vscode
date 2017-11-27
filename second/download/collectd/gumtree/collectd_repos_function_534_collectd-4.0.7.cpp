static void *plugin_read_thread (void *args)
{
	llentry_t   *le;
	read_func_t *rf;
	int          status;
	int          done;

	pthread_mutex_lock (&read_lock);

	while (read_loop != 0)
	{
		le = llist_head (list_read);
		done = 0;

		while ((read_loop != 0) && (le != NULL))
		{
			rf = (read_func_t *) le->value;

			if (rf->needs_read != TODO)
			{
				le = le->next;
				continue;
			}

			/* We will do this read function */
			rf->needs_read = ACTIVE;

			DEBUG ("[thread #%5lu] plugin: plugin_read_thread: Handling %s",
					(unsigned long int) pthread_self (), le->key);
			pthread_mutex_unlock (&read_lock);

			status = rf->callback ();
			done++;

			if (status != 0)
			{
				if (rf->wait_time < interval_g)
					rf->wait_time = interval_g;
				rf->wait_left = rf->wait_time;
				rf->wait_time = rf->wait_time * 2;
				if (rf->wait_time > 86400)
					rf->wait_time = 86400;

				NOTICE ("read-function of plugin `%s' "
						"failed. Will syspend it for %i "
						"seconds.", le->key, rf->wait_left);
			}
			else
			{
				rf->wait_left = 0;
				rf->wait_time = interval_g;
			}

			pthread_mutex_lock (&read_lock);

			rf->needs_read = DONE;
			le = le->next;
		} /* while (le != NULL) */

		if ((read_loop != 0) && (done == 0))
		{
			DEBUG ("[thread #%5lu] plugin: plugin_read_thread: Waiting on read_cond.",
					(unsigned long int) pthread_self ());
			pthread_cond_wait (&read_cond, &read_lock);
		}
	} /* while (read_loop) */

	pthread_mutex_unlock (&read_lock);

	pthread_exit (NULL);
}