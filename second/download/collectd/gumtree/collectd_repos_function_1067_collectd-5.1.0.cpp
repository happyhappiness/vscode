static int za_read (void)
{
	gauge_t  arc_hits, arc_misses, l2_hits, l2_misses;
	value_t  l2_io[2];

	get_kstat (&ksp, "zfs", 0, "arcstats");
	if (ksp == NULL)
	{
		ERROR ("zfs_arc plugin: Cannot find zfs:0:arcstats kstat.");
		return (-1);
	}

	/* Sizes */
	za_read_gauge (ksp, "size",    "cache_size", "arc");
	za_read_gauge (ksp, "l2_size", "cache_size", "L2");

        /* Operations */
	za_read_derive (ksp, "allocated","cache_operation", "allocated");
	za_read_derive (ksp, "deleted",  "cache_operation", "deleted");
	za_read_derive (ksp, "stolen",   "cache_operation", "stolen");

        /* Issue indicators */
        za_read_derive (ksp, "mutex_miss", "mutex_operation", "miss");
	za_read_derive (ksp, "hash_collisions", "hash_collisions", "");
	
        /* Evictions */
	za_read_derive (ksp, "evict_l2_cached",     "cache_eviction", "cached");
	za_read_derive (ksp, "evict_l2_eligible",   "cache_eviction", "eligible");
	za_read_derive (ksp, "evict_l2_ineligible", "cache_eviction", "ineligible");

	/* Hits / misses */
	za_read_derive (ksp, "demand_data_hits",         "cache_result", "demand_data-hit");
	za_read_derive (ksp, "demand_metadata_hits",     "cache_result", "demand_metadata-hit");
	za_read_derive (ksp, "prefetch_data_hits",       "cache_result", "prefetch_data-hit");
	za_read_derive (ksp, "prefetch_metadata_hits",   "cache_result", "prefetch_metadata-hit");
	za_read_derive (ksp, "demand_data_misses",       "cache_result", "demand_data-miss");
	za_read_derive (ksp, "demand_metadata_misses",   "cache_result", "demand_metadata-miss");
	za_read_derive (ksp, "prefetch_data_misses",     "cache_result", "prefetch_data-miss");
	za_read_derive (ksp, "prefetch_metadata_misses", "cache_result", "prefetch_metadata-miss");

	/* Ratios */
	arc_hits   = (gauge_t) get_kstat_value(ksp, "hits");
	arc_misses = (gauge_t) get_kstat_value(ksp, "misses");
	l2_hits    = (gauge_t) get_kstat_value(ksp, "l2_hits");
	l2_misses  = (gauge_t) get_kstat_value(ksp, "l2_misses");

	za_submit_ratio ("arc", arc_hits, arc_misses);
	za_submit_ratio ("L2", l2_hits, l2_misses);

	/* I/O */
	l2_io[0].derive = get_kstat_value(ksp, "l2_read_bytes");
	l2_io[1].derive = get_kstat_value(ksp, "l2_write_bytes");

	za_submit ("io_octets", "L2", l2_io, /* num values = */ 2);

	return (0);
}