static void rdt_dump_cgroups(void) {
  char cores[RDT_MAX_CORES * 4];

  if (g_rdt == NULL)
    return;

  DEBUG(RDT_PLUGIN ": Core Groups Dump");
  DEBUG(RDT_PLUGIN ":  groups count: %zu", g_rdt->num_groups);

  for (int i = 0; i < g_rdt->num_groups; i++) {

    memset(cores, 0, sizeof(cores));
    for (int j = 0; j < g_rdt->cgroups[i].num_cores; j++) {
      snprintf(cores + strlen(cores), sizeof(cores) - strlen(cores) - 1, " %d",
               g_rdt->cgroups[i].cores[j]);
    }

    DEBUG(RDT_PLUGIN ":  group[%d]:", i);
    DEBUG(RDT_PLUGIN ":    description: %s", g_rdt->cgroups[i].desc);
    DEBUG(RDT_PLUGIN ":    cores: %s", cores);
    DEBUG(RDT_PLUGIN ":    events: 0x%X", g_rdt->cgroups[i].events);
  }

  return;
}