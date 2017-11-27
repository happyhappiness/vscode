static int dpdk_events_init(void) {
  DPDK_EVENTS_TRACE();

  if (g_state & DPDK_EVENTS_STATE_CFG_ERR) {
    dpdk_events_shutdown();
    return -1;
  }

  int ret = dpdk_events_preinit();
  if (ret)
    return ret;

  return 0;
}