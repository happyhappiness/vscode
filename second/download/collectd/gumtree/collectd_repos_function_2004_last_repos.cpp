static int pmu_config_hw_events(oconfig_item_t *ci) {

  if (strcasecmp("HardwareEvents", ci->key) != 0) {
    return -EINVAL;
  }

  g_ctx.hw_events = calloc(ci->values_num, sizeof(char *));
  if (g_ctx.hw_events == NULL) {
    ERROR(PMU_PLUGIN ": Failed to allocate hw events.");
    return -ENOMEM;
  }

  for (int i = 0; i < ci->values_num; i++) {
    if (ci->values[i].type != OCONFIG_TYPE_STRING) {
      WARNING(PMU_PLUGIN ": The %s option requires string arguments.", ci->key);
      continue;
    }

    g_ctx.hw_events[g_ctx.hw_events_count] = strdup(ci->values[i].value.string);
    if (g_ctx.hw_events[g_ctx.hw_events_count] == NULL) {
      ERROR(PMU_PLUGIN ": Failed to allocate hw events entry.");
      return -ENOMEM;
    }

    g_ctx.hw_events_count++;
  }

  return 0;
}