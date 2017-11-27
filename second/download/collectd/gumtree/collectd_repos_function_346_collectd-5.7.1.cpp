static void aggregate(gauge_t *sum_by_state) /* {{{ */
{
  for (size_t state = 0; state < COLLECTD_CPU_STATE_MAX; state++)
    sum_by_state[state] = NAN;

  for (size_t cpu_num = 0; cpu_num < global_cpu_num; cpu_num++) {
    cpu_state_t *this_cpu_states = get_cpu_state(cpu_num, 0);

    this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].rate = NAN;

    for (size_t state = 0; state < COLLECTD_CPU_STATE_ACTIVE; state++) {
      if (!this_cpu_states[state].has_value)
        continue;

      RATE_ADD(sum_by_state[state], this_cpu_states[state].rate);
      if (state != COLLECTD_CPU_STATE_IDLE)
        RATE_ADD(this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].rate,
                 this_cpu_states[state].rate);
    }

    if (!isnan(this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].rate))
      this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].has_value = 1;

    RATE_ADD(sum_by_state[COLLECTD_CPU_STATE_ACTIVE],
             this_cpu_states[COLLECTD_CPU_STATE_ACTIVE].rate);
  }

#if defined(HAVE_PERFSTAT) /* {{{ */
  cdtime_t now = cdtime();
  perfstat_cpu_total_t cputotal = {0};

  if (!perfstat_cpu_total(NULL, &cputotal, sizeof(cputotal), 1)) {
    char errbuf[1024];
    WARNING("cpu plugin: perfstat_cpu_total: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    return;
  }

  /* Reset COLLECTD_CPU_STATE_ACTIVE */
  sum_by_state[COLLECTD_CPU_STATE_ACTIVE] = NAN;

  /* Physical Processor Utilization */
  total_rate(sum_by_state, COLLECTD_CPU_STATE_IDLE, (derive_t)cputotal.pidle,
             &total_conv[TOTAL_IDLE], now);
  total_rate(sum_by_state, COLLECTD_CPU_STATE_USER, (derive_t)cputotal.puser,
             &total_conv[TOTAL_USER], now);
  total_rate(sum_by_state, COLLECTD_CPU_STATE_SYSTEM, (derive_t)cputotal.psys,
             &total_conv[TOTAL_SYS], now);
  total_rate(sum_by_state, COLLECTD_CPU_STATE_WAIT, (derive_t)cputotal.pwait,
             &total_conv[TOTAL_WAIT], now);
#endif /* }}} HAVE_PERFSTAT */
}