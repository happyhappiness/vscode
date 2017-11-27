static void rrd_cache_flush (int timeout)
{
	rrd_cache_t *rc;
	time_t       now;

	char **keys = NULL;
	int    keys_num = 0;

	char *key;
	avl_iterator_t *iter;
	int i;

	if (cache == NULL)
		return;

	DEBUG ("Flushing cache, timeout = %i", timeout);

	now = time (NULL);

	/* Build a list of entries to be flushed */
	iter = avl_get_iterator (cache);
	while (avl_iterator_next (iter, (void *) &key, (void *) &rc) == 0)
	{
		DEBUG ("key = %s; age = %i;", key, now - rc->first_value);
		if ((now - rc->first_value) >= timeout)
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

		rrd_write_cache_entry (keys[i], rc);
		/* rc's value-list is free's by `rrd_write_cache_entry' */
		sfree (rc);
		sfree (key);
		keys[i] = NULL;
	} /* for (i = 0..keys_num) */

	free (keys);
	DEBUG ("Flushed %i value(s)", keys_num);

	cache_flush_last = now;
}