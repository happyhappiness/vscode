static int swap_read (void) /* {{{ */
{
        if(perfstat_memory_total(NULL, &pmemory, sizeof(perfstat_memory_total_t), 1) < 0)
	{
                char errbuf[1024];
                WARNING ("memory plugin: perfstat_memory_total failed: %s",
                        sstrerror (errno, errbuf, sizeof (errbuf)));
                return (-1);
        }
	swap_submit_gauge (NULL, "used", (gauge_t) (pmemory.pgsp_total - pmemory.pgsp_free) * pagesize);
	swap_submit_gauge (NULL, "free", (gauge_t) pmemory.pgsp_free * pagesize );

	return (0);
}