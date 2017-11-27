static int dpdk_events_preinit(void) {
  DPDK_EVENTS_TRACE();

  if (g_hc != NULL) {
    /* already initialized if config callback was called before init callback */
    DEBUG("dpdk_events_preinit: helper already initialized.");
    return 0;
  }

  int ret =
      dpdk_helper_init(DPDK_EVENTS_NAME, sizeof(dpdk_events_ctx_t), &g_hc);
  if (ret != 0) {
    ERROR(DPDK_EVENTS_PLUGIN ": failed to initialize %s helper(error: %s)",
          DPDK_EVENTS_NAME, strerror(ret));
    return ret;
  }

  dpdk_events_default_config();

  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(g_hc);
  for (int i = 0; i < RTE_MAX_ETHPORTS; i++) {
    ec->link_info[i].link_status = ETH_LINK_NA;
  }

  for (int i = 0; i < RTE_KEEPALIVE_MAXCORES; i++) {
    ec->core_info[i].lcore_state = ETH_LINK_NA;
  }

  return ret;
}