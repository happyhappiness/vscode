static int cache_update (const data_set_t *ds, const value_list_t *vl)
{
	char name[4*DATA_MAX_NAME_LEN];;
	value_cache_t *vc;
	int i;

	if (FORMAT_VL (name, sizeof (name), vl, ds) != 0)
		return (-1);

	pthread_mutex_lock (&cache_lock);

	vc = cache_search (name);

	/* pthread_mutex_lock is called by cache_insert. */
	if (vc == NULL)
		return (cache_insert (ds, vl));

	assert (vc->values_num == ds->ds_num);
	assert (vc->values_num == vl->values_len);

	/* Avoid floating-point exceptions due to division by zero. */
	if (vc->time >= vl->time)
	{
		pthread_mutex_unlock (&cache_lock);
		ERROR ("unixsock plugin: vc->time >= vl->time. vc->time = %u; "
				"vl->time = %u; vl = %s;",
				(unsigned int) vc->time, (unsigned int) vl->time,
				name);
		return (-1);
	} /* if (vc->time >= vl->time) */

	/*
	 * Update the values. This is possibly a lot more that you'd expect
	 * because we honor min and max values and handle counter overflows here.
	 */
	for (i = 0; i < ds->ds_num; i++)
	{
		if (ds->ds[i].type == DS_TYPE_COUNTER)
		{
			if (vl->values[i].counter < vc->counter[i])
			{
				if (vl->values[i].counter <= 4294967295U)
				{
					vc->gauge[i] = ((4294967295U - vl->values[i].counter)
							+ vc->counter[i]) / (vl->time - vc->time);
				}
				else
				{
					vc->gauge[i] = ((18446744073709551615ULL - vl->values[i].counter)
						+ vc->counter[i]) / (vl->time - vc->time);
				}
			}
			else
			{
				vc->gauge[i] = (vl->values[i].counter - vc->counter[i])
					/ (vl->time - vc->time);
			}

			vc->counter[i] = vl->values[i].counter;
		}
		else if (ds->ds[i].type == DS_TYPE_GAUGE)
		{
			vc->gauge[i] = vl->values[i].gauge;
			vc->counter[i] = 0;
		}
		else
		{
			vc->gauge[i] = NAN;
			vc->counter[i] = 0;
		}

		if (isnan (vc->gauge[i])
				|| (!isnan (ds->ds[i].min) && (vc->gauge[i] < ds->ds[i].min))
				|| (!isnan (ds->ds[i].max) && (vc->gauge[i] > ds->ds[i].max)))
			vc->gauge[i] = NAN;
	} /* for i = 0 .. ds->ds_num */

	vc->ds = ds;
	vc->time = vl->time;

	if (vc->time < cache_oldest)
		cache_oldest = vc->time;

	pthread_mutex_unlock (&cache_lock);
	return (0);
}