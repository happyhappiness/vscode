static int cache_insert (const data_set_t *ds, const value_list_t *vl)
{
	/* We're called from `cache_update' so we don't need to lock the mutex */
	value_cache_t *vc;
	int i;

	DEBUG ("unixsock plugin: cache_insert: ds->type = %s; ds->ds_num = %i;"
			" vl->values_len = %i;",
			ds->type, ds->ds_num, vl->values_len);
#if COLLECT_DEBUG
	assert (ds->ds_num == vl->values_len);
#else
	if (ds->ds_num != vl->values_len)
	{
		ERROR ("unixsock plugin: ds->type = %s: (ds->ds_num = %i) != "
				"(vl->values_len = %i)",
				ds->type, ds->ds_num, vl->values_len);
		return (-1);
	}
#endif

	vc = (value_cache_t *) malloc (sizeof (value_cache_t));
	if (vc == NULL)
	{
		char errbuf[1024];
		pthread_mutex_unlock (&cache_lock);
		ERROR ("unixsock plugin: malloc failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	vc->gauge = (gauge_t *) malloc (sizeof (gauge_t) * vl->values_len);
	if (vc->gauge == NULL)
	{
		char errbuf[1024];
		pthread_mutex_unlock (&cache_lock);
		ERROR ("unixsock plugin: malloc failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		free (vc);
		return (-1);
	}

	vc->counter = (counter_t *) malloc (sizeof (counter_t) * vl->values_len);
	if (vc->counter == NULL)
	{
		char errbuf[1024];
		pthread_mutex_unlock (&cache_lock);
		ERROR ("unixsock plugin: malloc failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		free (vc->gauge);
		free (vc);
		return (-1);
	}

	if (FORMAT_VL (vc->name, sizeof (vc->name), vl, ds))
	{
		pthread_mutex_unlock (&cache_lock);
		ERROR ("unixsock plugin: FORMAT_VL failed.");
		free (vc->counter);
		free (vc->gauge);
		free (vc);
		return (-1);
	}

	for (i = 0; i < ds->ds_num; i++)
	{
		if (ds->ds[i].type == DS_TYPE_COUNTER)
		{
			vc->gauge[i] = 0.0;
			vc->counter[i] = vl->values[i].counter;
		}
		else if (ds->ds[i].type == DS_TYPE_GAUGE)
		{
			vc->gauge[i] = vl->values[i].gauge;
			vc->counter[i] = 0;
		}
		else
		{
			vc->gauge[i] = 0.0;
			vc->counter[i] = 0;
		}
	}
	vc->values_num = ds->ds_num;
	vc->ds = ds;

	vc->next = cache_head;
	cache_head = vc;

	vc->time = vl->time;
	if ((vc->time < cache_oldest) || (-1 == cache_oldest))
		cache_oldest = vc->time;

	pthread_mutex_unlock (&cache_lock);
	return (0);
}