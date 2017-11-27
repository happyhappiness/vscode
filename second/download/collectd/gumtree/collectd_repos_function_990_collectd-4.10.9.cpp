static int za_read (void)
{
	gauge_t   arcsize, targetsize, minlimit, maxlimit, hits, misses, l2_size, l2_hits, l2_misses;
	counter_t demand_data_hits, demand_metadata_hits, prefetch_data_hits, prefetch_metadata_hits;
	counter_t demand_data_misses, demand_metadata_misses, prefetch_data_misses, prefetch_metadata_misses;
	counter_t l2_read_bytes, l2_write_bytes;
	kstat_t	 *ksp	= NULL;

	get_kstat (&ksp, "zfs", 0, "arcstats");
	if (ksp == NULL)
	{
		ERROR ("zfs_arc plugin: Cannot find zfs:0:arcstats kstat.");
		return (-1);
	}

	arcsize    = get_kstat_value(ksp, "size");
	targetsize = get_kstat_value(ksp, "c");
	minlimit   = get_kstat_value(ksp, "c_min");
	maxlimit   = get_kstat_value(ksp, "c_max");

	demand_data_hits       = get_kstat_value(ksp, "demand_data_hits");
	demand_metadata_hits   = get_kstat_value(ksp, "demand_metadata_hits");
	prefetch_data_hits     = get_kstat_value(ksp, "prefetch_data_hits");
	prefetch_metadata_hits = get_kstat_value(ksp, "prefetch_metadata_hits");

	demand_data_misses       = get_kstat_value(ksp, "demand_data_misses");
	demand_metadata_misses   = get_kstat_value(ksp, "demand_metadata_misses");
	prefetch_data_misses     = get_kstat_value(ksp, "prefetch_data_misses");
	prefetch_metadata_misses = get_kstat_value(ksp, "prefetch_metadata_misses");

	hits   = get_kstat_value(ksp, "hits");
	misses = get_kstat_value(ksp, "misses");

	l2_size        = get_kstat_value(ksp, "l2_size");
	l2_read_bytes  = get_kstat_value(ksp, "l2_read_bytes");
	l2_write_bytes = get_kstat_value(ksp, "l2_write_bytes");
	l2_hits        = get_kstat_value(ksp, "l2_hits");
	l2_misses      = get_kstat_value(ksp, "l2_misses");


	za_submit_size (arcsize, targetsize, minlimit, maxlimit);
	za_submit_gauge ("arc_l2_size", "", l2_size);

	za_submit_counts ("hits",   demand_data_hits,     demand_metadata_hits,
	                            prefetch_data_hits,   prefetch_metadata_hits);
	za_submit_counts ("misses", demand_data_misses,   demand_metadata_misses,
	                            prefetch_data_misses, prefetch_metadata_misses);

	za_submit_gauge ("arc_ratio", "L1", hits / (hits + misses));
	za_submit_gauge ("arc_ratio", "L2", l2_hits / (l2_hits + l2_misses));

	za_submit_bytes (l2_read_bytes, l2_write_bytes);

	return (0);
}