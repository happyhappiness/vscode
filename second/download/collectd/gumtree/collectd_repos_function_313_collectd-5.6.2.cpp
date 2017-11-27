static void cpu_commit(void) /* {{{ */
{
  gauge_t global_rates[COLLECTD_CPU_STATE_MAX] = {
      NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN /* Batman! */
  };

  if (report_num_cpu)
    cpu_commit_num_cpu((gauge_t)global_cpu_num);

  if (report_by_state && report_by_cpu && !report_percent) {
    cpu_commit_without_aggregation();
    return;
  }

  aggregate(global_rates);

  if (!report_by_cpu) {
    cpu_commit_one(-1, global_rates);
    return;
  }

  for (size_t cpu_num = 0; cpu_num < global_cpu_num; cpu_num++) {
    cpu_state_t *this_cpu_states = get_cpu_state(cpu_num, 0);
    gauge_t local_rates[COLLECTD_CPU_STATE_MAX] = {NAN, NAN, NAN, NAN, NAN,
                                                   NAN, NAN, NAN, NAN, NAN};

    for (size_t state = 0; state < COLLECTD_CPU_STATE_MAX; state++)
      if (this_cpu_states[state].has_value)
        local_rates[state] = this_cpu_states[state].rate;

    cpu_commit_one((int)cpu_num, local_rates);
  }
}