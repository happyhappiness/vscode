static int pmu_init(void) {
  int ret;

  DEBUG(PMU_PLUGIN ": %s:%d", __FUNCTION__, __LINE__);

  g_ctx.event_list = alloc_eventlist();
  if (g_ctx.event_list == NULL) {
    ERROR(PMU_PLUGIN ": Failed to allocate event list.");
    return -ENOMEM;
  }

  if (g_ctx.hw_cache_events) {
    ret =
        pmu_add_events(g_ctx.event_list, PERF_TYPE_HW_CACHE, g_hw_cache_events,
                       STATIC_ARRAY_SIZE(g_hw_cache_events));
    if (ret != 0) {
      ERROR(PMU_PLUGIN ": Failed to add hw cache events.");
      goto init_error;
    }
  }

  if (g_ctx.kernel_pmu_events) {
    ret = pmu_add_events(g_ctx.event_list, PERF_TYPE_HARDWARE,
                         g_kernel_pmu_events,
                         STATIC_ARRAY_SIZE(g_kernel_pmu_events));
    if (ret != 0) {
      ERROR(PMU_PLUGIN ": Failed to add kernel PMU events.");
      goto init_error;
    }
  }

  /* parse events names if config option is present and is not empty */
  if (g_ctx.hw_events_count) {

    ret = read_events(g_ctx.event_list_fn);
    if (ret != 0) {
      ERROR(PMU_PLUGIN ": Failed to read event list file '%s'.",
            g_ctx.event_list_fn);
      return ret;
    }

    ret = pmu_add_hw_events(g_ctx.event_list, g_ctx.hw_events,
                            g_ctx.hw_events_count);
    if (ret != 0) {
      ERROR(PMU_PLUGIN ": Failed to add hardware events.");
      goto init_error;
    }
  }

  if (g_ctx.sw_events) {
    ret = pmu_add_events(g_ctx.event_list, PERF_TYPE_SOFTWARE, g_sw_events,
                         STATIC_ARRAY_SIZE(g_sw_events));
    if (ret != 0) {
      ERROR(PMU_PLUGIN ": Failed to add software events.");
      goto init_error;
    }
  }

#if COLLECT_DEBUG
  pmu_dump_events();
#endif

  if (g_ctx.event_list->eventlist != NULL) {
    /* measure all processes */
    ret = pmu_setup_events(g_ctx.event_list, true, -1);
    if (ret != 0) {
      ERROR(PMU_PLUGIN ": Failed to setup perf events for the event list.");
      goto init_error;
    }
  } else {
    WARNING(PMU_PLUGIN
            ": Events list is empty. No events were setup for monitoring.");
  }

  return 0;

init_error:

  pmu_free_events(g_ctx.event_list);
  sfree(g_ctx.event_list);
  for (size_t i = 0; i < g_ctx.hw_events_count; i++) {
    sfree(g_ctx.hw_events[i]);
  }
  sfree(g_ctx.hw_events);
  g_ctx.hw_events_count = 0;

  return ret;
}