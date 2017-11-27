static void pmu_dump_config(void) {

  DEBUG(PMU_PLUGIN ": Config:");
  DEBUG(PMU_PLUGIN ":   hw_cache_events   : %d", g_ctx.hw_cache_events);
  DEBUG(PMU_PLUGIN ":   kernel_pmu_events : %d", g_ctx.kernel_pmu_events);
  DEBUG(PMU_PLUGIN ":   software_events   : %d", g_ctx.sw_events);

  for (size_t i = 0; i < g_ctx.hw_events_count; i++) {
    DEBUG(PMU_PLUGIN ":   hardware_events[%zu]: %s", i, g_ctx.hw_events[i]);
  }
}