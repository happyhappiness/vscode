static int rrd_cache_insert (const char *filename,
		const char *value, time_t value_time)
{
	rrd_cache_t *rc = NULL;
	int new_rc = 0;
	char **values_new;

	pthread_mutex_lock (&cache_lock);

	c_avl_get (cache, filename, (void *) &rc);

	if (rc == NULL)
	{
		rc = (rrd_cache_t *) malloc (sizeof (rrd_cache_t));
		if (rc == NULL)
			return (-1);
		rc->values_num = 0;
		rc->values = NULL;
		rc->first_value = 0;
		rc->last_value = 0;
		rc->flags = FLAG_NONE;
		new_rc = 1;
	}

	if (rc->last_value >= value_time)
	{
		pthread_mutex_unlock (&cache_lock);
		WARNING ("rrdtool plugin: (rc->last_value = %u) >= (value_time = %u)",
				(unsigned int) rc->last_value,
				(unsigned int) value_time);
		return (-1);
	}

	values_new = (char **) realloc ((void *) rc->values,
			(rc->values_num + 1) * sizeof (char *));
	if (values_new == NULL)
	{
		char errbuf[1024];
		void *cache_key = NULL;

		sstrerror (errno, errbuf, sizeof (errbuf));

		c_avl_remove (cache, filename, &cache_key, NULL);
		pthread_mutex_unlock (&cache_lock);

		ERROR ("rrdtool plugin: realloc failed: %s", errbuf);

		sfree (cache_key);
		sfree (rc->values);
		sfree (rc);
		return (-1);
	}
	rc->values = values_new;

	rc->values[rc->values_num] = strdup (value);
	if (rc->values[rc->values_num] != NULL)
		rc->values_num++;

	if (rc->values_num == 1)
		rc->first_value = value_time;
	rc->last_value = value_time;

	/* Insert if this is the first value */
	if (new_rc == 1)
	{
		void *cache_key = strdup (filename);

		if (cache_key == NULL)
		{
			char errbuf[1024];
			sstrerror (errno, errbuf, sizeof (errbuf));

			pthread_mutex_unlock (&cache_lock);

			ERROR ("rrdtool plugin: strdup failed: %s", errbuf);

			sfree (rc->values[0]);
			sfree (rc->values);
			sfree (rc);
			return (-1);
		}

		c_avl_insert (cache, cache_key, rc);
	}

	DEBUG ("rrdtool plugin: rrd_cache_insert: file = %s; "
			"values_num = %i; age = %u;",
			filename, rc->values_num,
			rc->last_value - rc->first_value);

	if ((rc->last_value - rc->first_value) >= cache_timeout)
	{
		/* XXX: If you need to lock both, cache_lock and queue_lock, at
		 * the same time, ALWAYS lock `cache_lock' first! */
		if (rc->flags != FLAG_QUEUED)
		{
			if (rrd_queue_cache_entry (filename) == 0)
				rc->flags = FLAG_QUEUED;
		}
		else
		{
			DEBUG ("rrdtool plugin: `%s' is already queued.", filename);
		}
	}

	if ((cache_timeout > 0) &&
			((time (NULL) - cache_flush_last) > cache_flush_timeout))
		rrd_cache_flush (cache_flush_timeout);


	pthread_mutex_unlock (&cache_lock);

	return (0);
}