static void rdt_free_cgroups(void) {
  for (int i = 0; i < RDT_MAX_CORES; i++) {
    sfree(g_rdt->cgroups[i].desc);

    sfree(g_rdt->cgroups[i].cores);
    g_rdt->cgroups[i].num_cores = 0;

    sfree(g_rdt->pgroups[i]);
  }
}