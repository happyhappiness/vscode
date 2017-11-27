static void rrd_cache_flush (cdtime_t timeout)
{
	rrd_cache_t *rc;
	cdtime_t     now;

	char **keys = NULL;
	int    keys_num = 0;

	char *key;
	c_avl_iterator_t *iter;

	DEBUG ("rrdtool plugin: Flushing cache, timeout = %.3f",
			CDTIME_T_TO_DOUBLE (timeout));

	now = cdtime ();
	timeout = TIME_T_TO_CDTIME_T (timeout);

	/* Build a list of entries to be flushed */
	iter = c_avl_get_iterator (cache);
	while (c_avl_iterator_next (iter, (void *) &key, (void *) &rc) == 0)
	{
		if (rc->flags != FLAG_NONE)
			continue;
		/* timeout == 0  =>  flush everything */
		else if ((timeout != 0)
				&& ((now - rc->first_value) < timeout))
			continue;
		else if (rc->values_num > 0)
		{
			int status;

			status = rrd_queue_enqueue (key, &queue_head,  &queue_tail);
			if (status == 0)
				rc->flags = FLAG_QUEUED;
		}
		else /* ancient and no values -> waste of memory */
		{
			char **tmp = realloc (keys,
					(keys_num + 1) * sizeof (char *));
			if (tmp == NULL)
			{
				char errbuf[1024];
				ERROR ("rrdtool plugin: "
						"realloc failed: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				c_avl_iterator_destroy (iter);
				sfree (keys);
				return;
			}
			keys = tmp;
			keys[keys_num] = key;
			keys_num++;
		}
	} /* while (c_avl_iterator_next) */
	c_avl_iterator_destroy (iter);

	for (int i = 0; i < keys_num; i++)
	{
		if (c_avl_remove (cache, keys[i], (void *) &key, (void *) &rc) != 0)
		{
			DEBUG ("rrdtool plugin: c_avl_remove (%s) failed.", keys[i]);
			continue;
		}

		assert (rc->values == NULL);
		assert (rc->values_num == 0);

		sfree (rc);
		sfree (key);
		keys[i] = NULL;
	} /* for (i = 0..keys_num) */

	sfree (keys);

	cache_flush_last = now;
}