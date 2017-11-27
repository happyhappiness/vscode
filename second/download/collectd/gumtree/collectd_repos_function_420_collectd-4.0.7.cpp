static rrd_cache_t *rrd_cache_insert (const char *filename,
		const char *value, time_t value_time)
{
	rrd_cache_t *rc = NULL;
	int new_rc = 0;

	if (cache != NULL)
		avl_get (cache, filename, (void *) &rc);

	if (rc == NULL)
	{
		rc = (rrd_cache_t *) malloc (sizeof (rrd_cache_t));
		if (rc == NULL)
			return (NULL);
		rc->values_num = 0;
		rc->values = NULL;
		rc->first_value = 0;
		rc->last_value = 0;
		new_rc = 1;
	}

	if (rc->last_value >= value_time)
	{
		WARNING ("rrdtool plugin: (rc->last_value = %u) >= (value_time = %u)",
				(unsigned int) rc->last_value,
				(unsigned int) value_time);
		return (NULL);
	}

	rc->values = (char **) realloc ((void *) rc->values,
			(rc->values_num + 1) * sizeof (char *));
	if (rc->values == NULL)
	{
		char errbuf[1024];
		ERROR ("rrdtool plugin: realloc failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		if (cache != NULL)
		{
			void *cache_key = NULL;
			avl_remove (cache, filename, &cache_key, NULL);
			sfree (cache_key);
		}
		free (rc);
		return (NULL);
	}

	rc->values[rc->values_num] = strdup (value);
	if (rc->values[rc->values_num] != NULL)
		rc->values_num++;

	if (rc->values_num == 1)
		rc->first_value = value_time;
	rc->last_value = value_time;

	/* Insert if this is the first value */
	if ((cache != NULL) && (new_rc == 1))
	{
		void *cache_key = strdup (filename);

		if (cache_key == NULL)
		{
			char errbuf[1024];
			ERROR ("rrdtool plugin: strdup failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			sfree (rc->values[0]);
			sfree (rc->values);
			sfree (rc);
			return (NULL);
		}

		avl_insert (cache, cache_key, rc);
	}

	DEBUG ("rrd_cache_insert (%s, %s, %u) = %p", filename, value,
			(unsigned int) value_time, (void *) rc);

	return (rc);
}