static double cpu_ns_to_percent(unsigned int node_cpus,
                                unsigned long long cpu_time_old,
                                unsigned long long cpu_time_new) {
  double percent = 0.0;
  unsigned long long cpu_time_diff = 0;
  double time_diff_sec = CDTIME_T_TO_DOUBLE(plugin_get_interval());

  if (node_cpus != 0 && time_diff_sec != 0 && cpu_time_old != 0) {
    cpu_time_diff = cpu_time_new - cpu_time_old;
    percent = ((double)(100 * cpu_time_diff)) /
              (time_diff_sec * node_cpus * NANOSEC_IN_SEC);
  }

  DEBUG(PLUGIN_NAME ": node_cpus=%u cpu_time_old=%llu cpu_time_new=%llu"
                    "cpu_time_diff=%llu time_diff_sec=%f percent=%f",
        node_cpus, cpu_time_old, cpu_time_new, cpu_time_diff, time_diff_sec,
        percent);

  return percent;
}