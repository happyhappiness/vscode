static void *rrd_queue_thread (void *data)
{
	while (42)
	{
		rrd_queue_t *queue_entry;
		rrd_cache_t *cache_entry;
		char **values;
		int    values_num;
		int    i;

		/* XXX: If you need to lock both, cache_lock and queue_lock, at
		 * the same time, ALWAYS lock `cache_lock' first! */

		/* wait until an entry is available */
		pthread_mutex_lock (&queue_lock);
		while ((queue_head == NULL) && (do_shutdown == 0))
			pthread_cond_wait (&queue_cond, &queue_lock);

		/* We're in the shutdown phase */
		if (queue_head == NULL)
		{
			pthread_mutex_unlock (&queue_lock);
			break;
		}

		/* Dequeue the first entry */
		queue_entry = queue_head;
		if (queue_head == queue_tail)
			queue_head = queue_tail = NULL;
		else
			queue_head = queue_head->next;

		/* Unlock the queue again */
		pthread_mutex_unlock (&queue_lock);

		/* We now need the cache lock so the entry isn't updated while
		 * we make a copy of it's values */
		pthread_mutex_lock (&cache_lock);

		c_avl_get (cache, queue_entry->filename, (void *) &cache_entry);

		values = cache_entry->values;
		values_num = cache_entry->values_num;

		cache_entry->values = NULL;
		cache_entry->values_num = 0;
		cache_entry->flags = FLAG_NONE;

		pthread_mutex_unlock (&cache_lock);

		/* Write the values to the RRD-file */
		srrd_update (queue_entry->filename, NULL, values_num, values);
		DEBUG ("rrdtool plugin: queue thread: Wrote %i values to %s",
				values_num, queue_entry->filename);

		for (i = 0; i < values_num; i++)
		{
			sfree (values[i]);
		}
		sfree (values);
		sfree (queue_entry->filename);
		sfree (queue_entry);
	} /* while (42) */

	pthread_mutex_lock (&cache_lock);
	c_avl_destroy (cache);
	cache = NULL;
	pthread_mutex_unlock (&cache_lock);

	pthread_exit ((void *) 0);
	return ((void *) 0);
}