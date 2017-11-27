static int swap_read (void) /* {{{ */
{
        if(perfstat_memory_total(NULL, &pmemory, sizeof(perfstat_memory_total_t), 1) < 0)
	{
                char errbuf[1024];
                WARNING ("memory plugin: perfstat_memory_total failed: %s",
                        sstrerror (errno, errbuf, sizeof (errbuf)));
                return (-1);
        }
	swap_submit ("used", (derive_t) (pmemory.pgsp_total - pmemory.pgsp_free) * pagesize, DS_TYPE_GAUGE);
	swap_submit ("free", (derive_t) pmemory.pgsp_free * pagesize , DS_TYPE_GAUGE);

	return (0);
}