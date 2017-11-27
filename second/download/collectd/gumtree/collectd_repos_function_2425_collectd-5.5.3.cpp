static void stop_write_threads (void) /* {{{ */
{
	write_queue_t *q;
	int i;

	if (write_threads == NULL)
		return;

	INFO ("collectd: Stopping %zu write threads.", write_threads_num);

	pthread_mutex_lock (&write_lock);
	write_loop = 0;
	DEBUG ("plugin: stop_write_threads: Signalling `write_cond'");
	pthread_cond_broadcast (&write_cond);
	pthread_mutex_unlock (&write_lock);

	for (i = 0; i < write_threads_num; i++)
	{
		if (pthread_join (write_threads[i], NULL) != 0)
		{
			ERROR ("plugin: stop_write_threads: pthread_join failed.");
		}
		write_threads[i] = (pthread_t) 0;
	}
	sfree (write_threads);
	write_threads_num = 0;

	pthread_mutex_lock (&write_lock);
	i = 0;
	for (q = write_queue_head; q != NULL; )
	{
		write_queue_t *q1 = q;
		plugin_value_list_free (q->vl);
		q = q->next;
		sfree (q1);
		i++;
	}
	write_queue_head = NULL;
	write_queue_tail = NULL;
	write_queue_length = 0;
	pthread_mutex_unlock (&write_lock);

	if (i > 0)
	{
		WARNING ("plugin: %i value list%s left after shutting down "
				"the write threads.",
				i, (i == 1) ? " was" : "s were");
	}
}