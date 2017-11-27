static int rdt_shutdown(void) {
  int ret;

  DEBUG(RDT_PLUGIN ": rdt_shutdown.");

  if (g_rdt == NULL)
    return (0);

  /* Stop monitoring */
  for (int i = 0; i < g_rdt->num_groups; i++) {
    pqos_mon_stop(g_rdt->pgroups[i]);
  }

  ret = pqos_fini();
  if (ret != PQOS_RETVAL_OK)
    ERROR(RDT_PLUGIN ": Error shutting down PQoS library.");

  rdt_free_cgroups();
  sfree(g_rdt);

  return (0);
}