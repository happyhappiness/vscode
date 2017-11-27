static int rdt_default_cgroups(void) {
  int ret;

  /* configure each core in separate group */
  for (unsigned i = 0; i < g_rdt->pqos_cpu->num_cores; i++) {
    char desc[DATA_MAX_NAME_LEN];
    uint64_t core = i;

    ssnprintf(desc, sizeof(desc), "%d", g_rdt->pqos_cpu->cores[i].lcore);

    /* set core group info */
    ret = cgroup_set(&g_rdt->cgroups[i], desc, &core, 1);
    if (ret < 0)
      return ret;
  }

  return g_rdt->pqos_cpu->num_cores;
}