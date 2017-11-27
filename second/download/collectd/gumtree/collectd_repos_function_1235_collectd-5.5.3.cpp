static int za_read (void)
{
	gauge_t  arc_hits, arc_misses, l2_hits, l2_misses;
	value_t  l2_io[2];
	kstat_t	 *ksp	= NULL;

#if KERNEL_LINUX
	long long int *llvalues = NULL;
	char file_contents[1024 * 10];
	char *fields[3];
	int numfields;
	ssize_t len;

	ksp = llist_create ();
	if (ksp == NULL)
	{
		ERROR ("zfs_arc plugin: `llist_create' failed.");
		return (-1);
	}

	len = read_file_contents (ZOL_ARCSTATS_FILE, file_contents, sizeof(file_contents) - 1);
	if (len > 1)
	{

		int i=0;
		char *pnl = file_contents;
		char *pnnl;

		file_contents[len] = '\0';

		while (pnl != NULL)
		{
			pnl = strchr(pnl, '\n');
			i++;
			if (pnl && (*pnl != '\0'))
				pnl++;
		}

		if (i > 0)
		{
			llentry_t *e;
			llvalues = malloc(sizeof(long long int) * i);
			if (llvalues == NULL)
			{
				ERROR ("zfs_arc plugin: `malloc' failed.");
				llist_destroy (ksp);
				return (-1);
			}
			int j = 0;

			pnl = file_contents;
			while (pnl != NULL)
			{
				pnnl = strchr(pnl, '\n');
				if (pnnl != NULL)
					*pnnl = '\0';

				numfields = strsplit (pnl, fields, 4);
				if (numfields == 3)
				{
					llvalues[j] = atoll (fields[2]);

					e = llentry_create (fields[0], &llvalues[j]);
					if (e == NULL)
					{
						ERROR ("zfs_arc plugin: `llentry_create' failed.");
					}
					else
					{
						llist_append (ksp, e);
					}
					j++;
				}
				pnl = pnnl;
				if (pnl != NULL)
					pnl ++;
			}
		}
	}

#elif !defined(__FreeBSD__) // Solaris
	get_kstat (&ksp, "zfs", 0, "arcstats");
	if (ksp == NULL)
	{
		ERROR ("zfs_arc plugin: Cannot find zfs:0:arcstats kstat.");
		return (-1);
	}
#endif

	/* Sizes */
	za_read_gauge (ksp, "size",    "cache_size", "arc");

	/* The "l2_size" value has disappeared from Solaris some time in
	 * early 2013, and has only reappeared recently in Solaris 11.2.
	 * Stop trying if we ever fail to read it, so we don't spam the log.
	 */
	static int l2_size_avail = 1;
	if (l2_size_avail && za_read_gauge (ksp, "l2_size", "cache_size", "L2") != 0)
		l2_size_avail = 0;

	/* Operations */
	za_read_derive (ksp, "deleted",  "cache_operation", "deleted");
#if __FreeBSD__
	za_read_derive (ksp, "allocated","cache_operation", "allocated");
#if defined(__FreeBSD_version) && (__FreeBSD_version < 1002501)
	/* stolen removed from sysctl kstat.zfs.misc.arcstats on FreeBSD 10.2+ */
	za_read_derive (ksp, "stolen",   "cache_operation", "stolen");
#endif
#endif

	/* Issue indicators */
	za_read_derive (ksp, "mutex_miss", "mutex_operations", "miss");
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
	arc_hits   = (gauge_t) get_zfs_value(ksp, "hits");
	arc_misses = (gauge_t) get_zfs_value(ksp, "misses");
	l2_hits    = (gauge_t) get_zfs_value(ksp, "l2_hits");
	l2_misses  = (gauge_t) get_zfs_value(ksp, "l2_misses");

	za_submit_ratio ("arc", arc_hits, arc_misses);
	za_submit_ratio ("L2", l2_hits, l2_misses);

	/* I/O */
	l2_io[0].derive = get_zfs_value(ksp, "l2_read_bytes");
	l2_io[1].derive = get_zfs_value(ksp, "l2_write_bytes");

	za_submit ("io_octets", "L2", l2_io, /* num values = */ 2);

#if defined(KERNEL_LINUX)
	if (llvalues != NULL)
	{
		free(llvalues);
	}
	if (ksp != NULL)
	{
		llist_destroy (ksp);
	}
#endif

	return (0);
}