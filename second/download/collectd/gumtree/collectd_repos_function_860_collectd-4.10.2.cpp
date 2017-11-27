static int cna_handle_disk_data (const char *hostname, /* {{{ */
		cfg_disk_t *cfg_disk, na_elem_t *data, int interval)
{
	time_t timestamp;
	na_elem_t *instances;
	na_elem_t *instance;
	na_elem_iter_t instance_iter;
	disk_t *worst_disk = NULL;

	if ((cfg_disk == NULL) || (data == NULL))
		return (EINVAL);
	
	timestamp = (time_t) na_child_get_uint64(data, "timestamp", 0);

	instances = na_elem_child (data, "instances");
	if (instances == NULL)
	{
		ERROR ("netapp plugin: cna_handle_disk_data: "
				"na_elem_child (\"instances\") failed "
				"for host %s.", hostname);
		return (-1);
	}

	/* Iterate over all children */
	instance_iter = na_child_iterator (instances);
	for (instance = na_iterator_next (&instance_iter);
			instance != NULL;
			instance = na_iterator_next(&instance_iter))
	{
		disk_t *old_data;
		disk_t  new_data;

		na_elem_iter_t counter_iterator;
		na_elem_t *counter;

		memset (&new_data, 0, sizeof (new_data));
		new_data.timestamp = timestamp;
		new_data.disk_busy_percent = NAN;

		old_data = get_disk(cfg_disk, na_child_get_string (instance, "name"));
		if (old_data == NULL)
			continue;

		/* Look for the "disk_busy" and "base_for_disk_busy" counters */
		counter_iterator = na_child_iterator(na_elem_child(instance, "counters"));
		for (counter = na_iterator_next(&counter_iterator);
				counter != NULL;
				counter = na_iterator_next(&counter_iterator))
		{
			const char *name;
			uint64_t value;

			name = na_child_get_string(counter, "name");
			if (name == NULL)
				continue;

			value = na_child_get_uint64(counter, "value", UINT64_MAX);
			if (value == UINT64_MAX)
				continue;

			if (strcmp(name, "disk_busy") == 0)
			{
				new_data.disk_busy = value;
				new_data.flags |= HAVE_DISK_BUSY;
			}
			else if (strcmp(name, "base_for_disk_busy") == 0)
			{
				new_data.base_for_disk_busy = value;
				new_data.flags |= HAVE_DISK_BASE;
			}
			else
			{
				DEBUG ("netapp plugin: cna_handle_disk_data: "
						"Counter not handled: %s = %"PRIu64,
						name, value);
			}
		}

		/* If all required counters are available and did not just wrap around,
		 * calculate the busy percentage. Otherwise, the value is initialized to
		 * NAN at the top of the for-loop. */
		if (HAS_ALL_FLAGS (old_data->flags, HAVE_DISK_BUSY | HAVE_DISK_BASE)
				&& HAS_ALL_FLAGS (new_data.flags, HAVE_DISK_BUSY | HAVE_DISK_BASE)
				&& (new_data.disk_busy >= old_data->disk_busy)
				&& (new_data.base_for_disk_busy > old_data->base_for_disk_busy))
		{
			uint64_t busy_diff;
			uint64_t base_diff;

			busy_diff = new_data.disk_busy - old_data->disk_busy;
			base_diff = new_data.base_for_disk_busy - old_data->base_for_disk_busy;

			new_data.disk_busy_percent = 100.0
				* ((gauge_t) busy_diff) / ((gauge_t) base_diff);
		}

		/* Clear HAVE_* flags */
		old_data->flags &= ~HAVE_DISK_ALL;

		/* Copy data */
		old_data->timestamp = new_data.timestamp;
		old_data->disk_busy = new_data.disk_busy;
		old_data->base_for_disk_busy = new_data.base_for_disk_busy;
		old_data->disk_busy_percent = new_data.disk_busy_percent;

		/* Copy flags */
		old_data->flags |= (new_data.flags & HAVE_DISK_ALL);

		if ((worst_disk == NULL)
				|| (worst_disk->disk_busy_percent < old_data->disk_busy_percent))
			worst_disk = old_data;
	} /* for (all disks) */

	if ((cfg_disk->flags & CFG_DISK_BUSIEST) && (worst_disk != NULL))
		submit_double (hostname, "system", "percent", "disk_busy",
				worst_disk->disk_busy_percent, timestamp, interval);

	return (0);
}