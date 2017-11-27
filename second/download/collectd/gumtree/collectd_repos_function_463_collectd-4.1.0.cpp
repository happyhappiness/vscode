static void rrd_cache_flush (int timeout)
{
	rrd_cache_t *rc;
	time_t       now;

	char **keys = NULL;
	int    keys_num = 0;

	char *key;
	avl_iterator_t *iter;
	int i;

	DEBUG ("Flushing cache, timeout = %i", timeout);

	now = time (NULL);

	/* Build a list of entries to be flushed */
	iter = avl_get_iterator (cache);
	while (avl_iterator_next (iter, (void *) &key, (void *) &rc) == 0)
	{
		DEBUG ("key = %s; age = %i;", key, now - rc->first_value);

		if (rc->flags == FLAG_QUEUED)
			continue;
		else if ((now - rc->first_value) < timeout)
			continue;
		else if (rc->values_num > 0)
		{
			if (rrd_queue_cache_entry (key) == 0)
				rc->flags = FLAG_QUEUED;
		}
		else /* ancient and no values -> waste of memory */
		{
			keys = (char **) realloc ((void *) keys,
					(keys_num + 1) * sizeof (char *));
			if (keys == NULL)
			{
				char errbuf[1024];
				ERROR ("rrdtool plugin: "
						"realloc failed: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				avl_iterator_destroy (iter);
				return;
			}
			keys[keys_num] = key;
			keys_num++;
		}
	} /* while (avl_iterator_next) */
	avl_iterator_destroy (iter);
	
	for (i = 0; i < keys_num; i++)
	{
		if (avl_remove (cache, keys[i], (void *) &key, (void *) &rc) != 0)
		{
			DEBUG ("avl_remove (%s) failed.", keys[i]);
			continue;
		}

		assert (rc->values == NULL);
		assert (rc->values_num == 0);

		sfree (rc);
		sfree (key);
		keys[i] = NULL;
	} /* for (i = 0..keys_num) */

	free (keys);
	DEBUG ("Flushed %i value(s)", keys_num);

	cache_flush_last = now;
}