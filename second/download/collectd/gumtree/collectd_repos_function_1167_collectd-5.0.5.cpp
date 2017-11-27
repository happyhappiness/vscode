static int lpar_init (void)
{
	int status;

	/* Retrieve the initial metrics. Returns the number of structures filled. */
	status = perfstat_partition_total (/* name = */ NULL, /* (must be NULL) */
			&lparstats_old, sizeof (perfstat_partition_total_t),
			/* number = */ 1 /* (must be 1) */);
	if (status != 1)
	{
		char errbuf[1024];
		ERROR ("lpar plugin: perfstat_partition_total failed: %s (%i)",
				sstrerror (errno, errbuf, sizeof (errbuf)),
				status);
		return (-1);
	}

#if PERFSTAT_SUPPORTS_DONATION
	if (!lparstats_old.type.b.shared_enabled
		       	&& lparstats_old.type.b.donate_enabled)
	{
		donate_flag = 1;
	}
#endif

	if (pool_stats && !lparstats_old.type.b.pool_util_authority)
	{
		WARNING ("lpar plugin: This partition does not have pool authority. "
				"Disabling CPU pool statistics collection.");
		pool_stats = 0;
	}

	return (0);
}