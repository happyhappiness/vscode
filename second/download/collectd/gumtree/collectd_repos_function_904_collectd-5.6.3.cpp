static int turbostat_read(void) {
  int ret;

  if (!allocated) {
    if ((ret = setup_all_buffers()) < 0)
      return ret;
  }

  if (for_all_proc_cpus(cpu_is_not_present)) {
    free_all_buffers();
    if ((ret = setup_all_buffers()) < 0)
      return ret;
    if (for_all_proc_cpus(cpu_is_not_present)) {
      ERROR("turbostat plugin: CPU appeared just after "
            "initialization");
      return -1;
    }
  }

  /* Saving the scheduling affinity, as it will be modified by get_counters */
  if (sched_getaffinity(0, cpu_saved_affinity_setsize,
                        cpu_saved_affinity_set) != 0) {
    ERROR("turbostat plugin: Unable to save the CPU affinity");
    return -1;
  }

  if (!initialized) {
    if ((ret = for_all_cpus(get_counters, EVEN_COUNTERS)) < 0)
      goto out;
    time_even = cdtime();
    is_even = 1;
    initialized = 1;
    ret = 0;
    goto out;
  }

  if (is_even) {
    if ((ret = for_all_cpus(get_counters, ODD_COUNTERS)) < 0)
      goto out;
    time_odd = cdtime();
    is_even = 0;
    time_delta = time_odd - time_even;
    if ((ret = for_all_cpus_delta(ODD_COUNTERS, EVEN_COUNTERS)) < 0)
      goto out;
    if ((ret = for_all_cpus(submit_counters, DELTA_COUNTERS)) < 0)
      goto out;
  } else {
    if ((ret = for_all_cpus(get_counters, EVEN_COUNTERS)) < 0)
      goto out;
    time_even = cdtime();
    is_even = 1;
    time_delta = time_even - time_odd;
    if ((ret = for_all_cpus_delta(EVEN_COUNTERS, ODD_COUNTERS)) < 0)
      goto out;
    if ((ret = for_all_cpus(submit_counters, DELTA_COUNTERS)) < 0)
      goto out;
  }
  ret = 0;
out:
  /*
   * Let's restore the affinity
   * This might fail if the number of CPU changed, but we can't do anything in
   * that case..
   */
  (void)sched_setaffinity(0, cpu_saved_affinity_setsize,
                          cpu_saved_affinity_set);
  return ret;
}