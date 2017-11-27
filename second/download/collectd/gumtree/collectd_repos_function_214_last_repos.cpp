static int rdt_is_core_id_valid(int core_id) {

  for (int i = 0; i < g_rdt->pqos_cpu->num_cores; i++)
    if (core_id == g_rdt->pqos_cpu->cores[i].lcore)
      return 1;

  return 0;
}