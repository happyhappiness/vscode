static int pmu_config(oconfig_item_t *ci) {

  DEBUG(PMU_PLUGIN ": %s:%d", __FUNCTION__, __LINE__);

  for (int i = 0; i < ci->children_num; i++) {
    int ret = 0;
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("ReportHardwareCacheEvents", child->key) == 0) {
      ret = cf_util_get_boolean(child, &g_ctx.hw_cache_events);
    } else if (strcasecmp("ReportKernelPMUEvents", child->key) == 0) {
      ret = cf_util_get_boolean(child, &g_ctx.kernel_pmu_events);
    } else if (strcasecmp("EventList", child->key) == 0) {
      ret = cf_util_get_string_buffer(child, g_ctx.event_list_fn,
                                      sizeof(g_ctx.event_list_fn));
    } else if (strcasecmp("HardwareEvents", child->key) == 0) {
      ret = pmu_config_hw_events(child);
    } else if (strcasecmp("ReportSoftwareEvents", child->key) == 0) {
      ret = cf_util_get_boolean(child, &g_ctx.sw_events);
    } else {
      ERROR(PMU_PLUGIN ": Unknown configuration parameter \"%s\".", child->key);
      ret = -1;
    }

    if (ret != 0) {
      DEBUG(PMU_PLUGIN ": %s:%d ret=%d", __FUNCTION__, __LINE__, ret);
      return ret;
    }
  }

#if COLLECT_DEBUG
  pmu_dump_config();
#endif

  return 0;
}