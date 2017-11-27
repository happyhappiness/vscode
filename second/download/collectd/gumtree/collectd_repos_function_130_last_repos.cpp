static int dpdk_stats_shutdown(void) {
  DPDK_STATS_TRACE();

  dpdk_helper_shutdown(g_hc);
  g_hc = NULL;

  return 0;
}