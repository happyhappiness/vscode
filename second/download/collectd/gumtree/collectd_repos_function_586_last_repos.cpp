static int dpdk_events_read(user_data_t *ud) {
  DPDK_EVENTS_TRACE();

  if (g_hc == NULL) {
    ERROR(DPDK_EVENTS_PLUGIN ": plugin not initialized.");
    return -1;
  }

  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(g_hc);
  int ls_ret = -1, ka_ret = -1;

  int cmd_res = 0;
  if (ec->config.link_status.enabled) {
    ls_ret = dpdk_helper_command(g_hc, DPDK_CMD_GET_EVENTS, &cmd_res,
                                 ec->config.interval);
    if (cmd_res == 0 && ls_ret == 0) {
      dpdk_events_link_status_dispatch(g_hc);
    }
  }

  if (ec->config.keep_alive.enabled) {
    ka_ret = dpdk_event_keep_alive_shm_open();
    if (ka_ret) {
      ERROR(DPDK_EVENTS_PLUGIN
            ": %s : error %d in dpdk_event_keep_alive_shm_open()",
            __FUNCTION__, ka_ret);
    } else
      dpdk_events_keep_alive_dispatch(g_hc);
  }

  if (!((cmd_res || ls_ret) == 0 || ka_ret == 0)) {
    ERROR(DPDK_EVENTS_PLUGIN ": Read failure for all enabled event types");
    return -1;
  }

  return 0;
}