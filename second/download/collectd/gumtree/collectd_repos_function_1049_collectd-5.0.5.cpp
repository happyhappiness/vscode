static int za_read (void)
{
	gauge_t  arc_size, l2_size;
	derive_t demand_data_hits,
		 demand_metadata_hits,
		 prefetch_data_hits,
		 prefetch_metadata_hits,
		 demand_data_misses,
		 demand_metadata_misses,
		 prefetch_data_misses,
		 prefetch_metadata_misses;
	gauge_t  arc_hits, arc_misses, l2_hits, l2_misses;
	value_t  l2_io[2];
	kstat_t	 *ksp	= NULL;

	get_kstat (&ksp, "zfs", 0, "arcstats");
	if (ksp == NULL)
	{
		ERROR ("zfs_arc plugin: Cannot find zfs:0:arcstats kstat.");
		return (-1);
	}

	/* Sizes */
	arc_size   = get_kstat_value(ksp, "size");
	l2_size    = get_kstat_value(ksp, "l2_size");

	za_submit_gauge ("cache_size", "arc", arc_size);
	za_submit_gauge ("cache_size", "L2", l2_size);

	/* Hits / misses */
	demand_data_hits       = get_kstat_value(ksp, "demand_data_hits");
	demand_metadata_hits   = get_kstat_value(ksp, "demand_metadata_hits");
	prefetch_data_hits     = get_kstat_value(ksp, "prefetch_data_hits");
	prefetch_metadata_hits = get_kstat_value(ksp, "prefetch_metadata_hits");

	demand_data_misses       = get_kstat_value(ksp, "demand_data_misses");
	demand_metadata_misses   = get_kstat_value(ksp, "demand_metadata_misses");
	prefetch_data_misses     = get_kstat_value(ksp, "prefetch_data_misses");
	prefetch_metadata_misses = get_kstat_value(ksp, "prefetch_metadata_misses");

	za_submit_derive ("cache_result", "demand_data-hit",       demand_data_hits);
	za_submit_derive ("cache_result", "demand_metadata-hit",   demand_metadata_hits);
	za_submit_derive ("cache_result", "prefetch_data-hit",     prefetch_data_hits);
	za_submit_derive ("cache_result", "prefetch_metadata-hit", prefetch_metadata_hits);

	za_submit_derive ("cache_result", "demand_data-miss",       demand_data_misses);
	za_submit_derive ("cache_result", "demand_metadata-miss",   demand_metadata_misses);
	za_submit_derive ("cache_result", "prefetch_data-miss",     prefetch_data_misses);
	za_submit_derive ("cache_result", "prefetch_metadata-miss", prefetch_metadata_misses);

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