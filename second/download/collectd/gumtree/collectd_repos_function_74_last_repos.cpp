static void pcpu_submit(virDomainPtr dom, struct lv_info *info) {
#ifdef HAVE_CPU_STATS
  if (extra_stats & ex_stats_pcpu)
    submit_derive2("ps_cputime", info->total_user_cpu_time,
                   info->total_syst_cpu_time, dom, NULL);
#endif /* HAVE_CPU_STATS */
}