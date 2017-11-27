static int get_perf_events(virDomainPtr domain) {
  virDomainStatsRecordPtr *stats = NULL;
  /* virDomainListGetStats requires a NULL terminated list of domains */
  virDomainPtr domain_array[] = {domain, NULL};

  int status =
      virDomainListGetStats(domain_array, VIR_DOMAIN_STATS_PERF, &stats, 0);
  if (status == -1) {
    ERROR("virt plugin: virDomainListGetStats failed with status %i.", status);
    return status;
  }

  for (int i = 0; i < status; ++i)
    perf_submit(stats[i]);

  virDomainStatsRecordListFree(stats);
  return 0;
}