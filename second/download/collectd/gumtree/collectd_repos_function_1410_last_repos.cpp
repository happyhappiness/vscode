static int swap_read(void) /* {{{ */
{
  perfstat_memory_total_t pmemory = {0};
  int status;

  gauge_t total;
  gauge_t free;
  gauge_t reserved;

  status =
      perfstat_memory_total(NULL, &pmemory, sizeof(perfstat_memory_total_t), 1);
  if (status < 0) {
    char errbuf[1024];
    WARNING("swap plugin: perfstat_memory_total failed: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  total = (gauge_t)(pmemory.pgsp_total * pagesize);
  free = (gauge_t)(pmemory.pgsp_free * pagesize);
  reserved = (gauge_t)(pmemory.pgsp_rsvd * pagesize);

  swap_submit_usage(NULL, total - free, free, "reserved", reserved);

  if (report_io) {
    swap_submit_derive("in", (derive_t)pmemory.pgspins * pagesize);
    swap_submit_derive("out", (derive_t)pmemory.pgspouts * pagesize);
  }

  return 0;
}