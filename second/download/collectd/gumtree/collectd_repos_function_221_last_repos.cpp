static int rdt_init(void) {
  int ret;

  if (g_state == CONFIGURATION_ERROR)
    return -1;

  ret = rdt_preinit();
  if (ret != 0)
    return ret;

  /* Start monitoring */
  for (int i = 0; i < g_rdt->num_groups; i++) {
    rdt_core_group_t *cg = &g_rdt->cgroups[i];

    ret = pqos_mon_start(cg->num_cores, cg->cores, cg->events, (void *)cg->desc,
                         g_rdt->pgroups[i]);

    if (ret != PQOS_RETVAL_OK)
      ERROR(RDT_PLUGIN ": Error starting monitoring group %s (pqos status=%d)",
            cg->desc, ret);
  }

  return 0;
}