static void pmu_dispatch_data(void) {

  struct event *e;

  for (e = g_ctx.event_list->eventlist; e; e = e->next) {
    uint64_t all_value = 0;
    int event_enabled = 0;
    for (int i = 0; i < g_ctx.event_list->num_cpus; i++) {

      if (e->efd[i].fd < 0)
        continue;

      event_enabled++;

      /* If there are more events than counters, the kernel uses time
       * multiplexing. With multiplexing, at the end of the run,
       * the counter is scaled basing on total time enabled vs time running.
       * final_count = raw_count * time_enabled/time_running
       */
      uint64_t value = event_scaled_value(e, i);
      all_value += value;

      /* get meta data with information about scaling */
      meta_data_t *meta = pmu_meta_data_create(&e->efd[i]);

      /* dispatch per CPU value */
      pmu_submit_counter(i, e->event, value, meta);

      meta_data_destroy(meta);
    }

    if (event_enabled > 0) {
      DEBUG(PMU_PLUGIN ": %-20s %'10lu", e->event, all_value);
      /* dispatch all CPU value */
      pmu_submit_counter(-1, e->event, all_value, NULL);
    }
  }
}