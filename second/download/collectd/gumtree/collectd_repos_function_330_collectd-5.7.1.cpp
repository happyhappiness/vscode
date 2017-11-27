static int rdt_config_cgroups(oconfig_item_t *item) {
  int n = 0;
  enum pqos_mon_event events = 0;

  if (item == NULL) {
    DEBUG(RDT_PLUGIN ": cgroups_config: Invalid argument.");
    return (-EINVAL);
  }

  DEBUG(RDT_PLUGIN ": Core groups [%d]:", item->values_num);
  for (int j = 0; j < item->values_num; j++) {
    if (item->values[j].type != OCONFIG_TYPE_STRING) {
      ERROR(RDT_PLUGIN ": given core group value is not a string [idx=%d]", j);
      return (-EINVAL);
    }
    DEBUG(RDT_PLUGIN ":  [%d]: %s", j, item->values[j].value.string);
  }

  n = oconfig_to_cgroups(item, g_rdt->cgroups, RDT_MAX_CORES,
                         g_rdt->pqos_cpu->num_cores - 1);
  if (n < 0) {
    rdt_free_cgroups();
    ERROR(RDT_PLUGIN ": Error parsing core groups configuration.");
    return (-EINVAL);
  }

  if (n == 0) {
    /* create default core groups if "Cores" config option is empty */
    n = rdt_default_cgroups();
    if (n < 0) {
      rdt_free_cgroups();
      ERROR(RDT_PLUGIN ": Error creating default core groups configuration.");
      return n;
    }
    INFO(RDT_PLUGIN
         ": No core groups configured. Default core groups created.");
  }

  /* Get all available events on this platform */
  for (int i = 0; i < g_rdt->cap_mon->u.mon->num_events; i++)
    events |= g_rdt->cap_mon->u.mon->events[i].type;

  events &= ~(PQOS_PERF_EVENT_LLC_MISS);

  DEBUG(RDT_PLUGIN ": Number of cores in the system: %u",
        g_rdt->pqos_cpu->num_cores);
  DEBUG(RDT_PLUGIN ": Available events to monitor: %#x", events);

  g_rdt->num_groups = n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      int found = 0;
      found = cgroup_cmp(&g_rdt->cgroups[j], &g_rdt->cgroups[i]);
      if (found != 0) {
        rdt_free_cgroups();
        ERROR(RDT_PLUGIN ": Cannot monitor same cores in different groups.");
        return (-EINVAL);
      }
    }

    g_rdt->cgroups[i].events = events;
    g_rdt->pgroups[i] = calloc(1, sizeof(*g_rdt->pgroups[i]));
    if (g_rdt->pgroups[i] == NULL) {
      rdt_free_cgroups();
      ERROR(RDT_PLUGIN ": Failed to allocate memory for monitoring data.");
      return (-ENOMEM);
    }
  }

  return (0);
}