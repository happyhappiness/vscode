static void rdt_dump_data(void) {
  /*
   * CORE - monitored group of cores
   * RMID - Resource Monitoring ID associated with the monitored group
   * LLC - last level cache occupancy
   * MBL - local memory bandwidth
   * MBR - remote memory bandwidth
   */
  DEBUG("  CORE     RMID    LLC[KB]   MBL[MB]    MBR[MB]");
  for (int i = 0; i < g_rdt->num_groups; i++) {

    const struct pqos_event_values *pv = &g_rdt->pgroups[i]->values;

    double llc = bytes_to_kb(pv->llc);
    double mbr = bytes_to_mb(pv->mbm_remote_delta);
    double mbl = bytes_to_mb(pv->mbm_local_delta);

    DEBUG(" [%s] %8u %10.1f %10.1f %10.1f", g_rdt->cgroups[i].desc,
          g_rdt->pgroups[i]->poll_ctx[0].rmid, llc, mbl, mbr);
  }
}