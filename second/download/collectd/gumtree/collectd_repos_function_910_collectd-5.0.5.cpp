static int cna_handle_wafl_data (const char *hostname, cfg_wafl_t *cfg_wafl, /* {{{ */
		na_elem_t *data, int interval)
{
	cfg_wafl_t perf_data;
	const char *plugin_inst;

	na_elem_t *instances;
	na_elem_t *counter;
	na_elem_iter_t counter_iter;

	memset (&perf_data, 0, sizeof (perf_data));
	
	perf_data.timestamp = cna_child_get_cdtime (data);

	instances = na_elem_child(na_elem_child (data, "instances"), "instance-data");
	if (instances == NULL)
	{
		ERROR ("netapp plugin: cna_handle_wafl_data: "
				"na_elem_child (\"instances\") failed "
				"for host %s.", hostname);
		return (-1);
	}

	plugin_inst = na_child_get_string(instances, "name");
	if (plugin_inst == NULL)
	{
		ERROR ("netapp plugin: cna_handle_wafl_data: "
				"na_child_get_string (\"name\") failed "
				"for host %s.", hostname);
		return (-1);
	}

	/* Iterate over all counters */
	counter_iter = na_child_iterator (na_elem_child (instances, "counters"));
	for (counter = na_iterator_next (&counter_iter);
			counter != NULL;
			counter = na_iterator_next (&counter_iter))
	{
		const char *name;
		uint64_t value;

		name = na_child_get_string(counter, "name");
		if (name == NULL)
			continue;

		value = na_child_get_uint64(counter, "value", UINT64_MAX);
		if (value == UINT64_MAX)
			continue;

		if (!strcmp(name, "name_cache_hit")) {
			perf_data.name_cache_hit = value;
			perf_data.flags |= HAVE_WAFL_NAME_CACHE_HIT;
		} else if (!strcmp(name, "name_cache_miss")) {
			perf_data.name_cache_miss = value;
			perf_data.flags |= HAVE_WAFL_NAME_CACHE_MISS;
		} else if (!strcmp(name, "find_dir_hit")) {
			perf_data.find_dir_hit = value;
			perf_data.flags |= HAVE_WAFL_FIND_DIR_HIT;
		} else if (!strcmp(name, "find_dir_miss")) {
			perf_data.find_dir_miss = value;
			perf_data.flags |= HAVE_WAFL_FIND_DIR_MISS;
		} else if (!strcmp(name, "buf_hash_hit")) {
			perf_data.buf_hash_hit = value;
			perf_data.flags |= HAVE_WAFL_BUF_HASH_HIT;
		} else if (!strcmp(name, "buf_hash_miss")) {
			perf_data.buf_hash_miss = value;
			perf_data.flags |= HAVE_WAFL_BUF_HASH_MISS;
		} else if (!strcmp(name, "inode_cache_hit")) {
			perf_data.inode_cache_hit = value;
			perf_data.flags |= HAVE_WAFL_INODE_CACHE_HIT;
		} else if (!strcmp(name, "inode_cache_miss")) {
			perf_data.inode_cache_miss = value;
			perf_data.flags |= HAVE_WAFL_INODE_CACHE_MISS;
		} else {
			DEBUG("netapp plugin: cna_handle_wafl_data: "
					"Found unexpected child: %s "
					"for host %s.", name, hostname);
		}
	}

	return (submit_wafl_data (hostname, plugin_inst, cfg_wafl, &perf_data, interval));
}