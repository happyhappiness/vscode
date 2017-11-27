static int pmu_shutdown(void) {

  DEBUG(PMU_PLUGIN ": %s:%d", __FUNCTION__, __LINE__);

  pmu_free_events(g_ctx.event_list);
  sfree(g_ctx.event_list);
  for (size_t i = 0; i < g_ctx.hw_events_count; i++) {
    sfree(g_ctx.hw_events[i]);
  }
  sfree(g_ctx.hw_events);
  g_ctx.hw_events_count = 0;

  return 0;
}