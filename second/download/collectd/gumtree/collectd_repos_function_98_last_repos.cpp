static int get_domain_metrics(domain_t *domain) {
  struct lv_info info;

  if (!domain || !domain->ptr) {
    ERROR(PLUGIN_NAME ": get_domain_metrics: NULL pointer");
    return -1;
  }

  init_lv_info(&info);
  int status = lv_domain_info(domain->ptr, &info);
  if (status != 0) {
    ERROR(PLUGIN_NAME " plugin: virDomainGetInfo failed with status %i.",
          status);
    return -1;
  }

  if (extra_stats & ex_stats_domain_state) {
#ifdef HAVE_DOM_REASON
    /* At this point we already know domain's state from virDomainGetInfo call,
     * however it doesn't provide a reason for entering particular state.
     * We need to get it from virDomainGetState.
     */
    GET_STATS(get_domain_state, "domain reason", domain->ptr);
#else
    /* virDomainGetState is not available. Submit 0, which corresponds to
     * unknown reason. */
    domain_state_submit(domain->ptr, info.di.state, 0);
#endif
  }

  /* Gather remaining stats only for running domains */
  if (info.di.state != VIR_DOMAIN_RUNNING)
    return 0;

  pcpu_submit(domain->ptr, &info);
  cpu_submit(domain, info.di.cpuTime);

  memory_submit(domain->ptr, (gauge_t)info.di.memory * 1024);

  GET_STATS(get_vcpu_stats, "vcpu stats", domain->ptr, info.di.nrVirtCpu);
  GET_STATS(get_memory_stats, "memory stats", domain->ptr);

#ifdef HAVE_PERF_STATS
  if (extra_stats & ex_stats_perf)
    GET_STATS(get_perf_events, "performance monitoring events", domain->ptr);
#endif

#ifdef HAVE_FS_INFO
  if (extra_stats & ex_stats_fs_info)
    GET_STATS(get_fs_info, "file system info", domain->ptr);
#endif

#ifdef HAVE_DISK_ERR
  if (extra_stats & ex_stats_disk_err)
    GET_STATS(get_disk_err, "disk errors", domain->ptr);
#endif

#ifdef HAVE_JOB_STATS
  if (extra_stats &
      (ex_stats_job_stats_completed | ex_stats_job_stats_background))
    GET_STATS(get_job_stats, "job stats", domain->ptr);
#endif

  /* Update cached virDomainInfo. It has to be done after cpu_submit */
  memcpy(&domain->info, &info.di, sizeof(domain->info));
  return 0;
}