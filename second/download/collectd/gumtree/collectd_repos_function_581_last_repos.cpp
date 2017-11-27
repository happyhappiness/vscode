int dpdk_helper_command_handler(dpdk_helper_ctx_t *phc, enum DPDK_CMD cmd) {
  if (phc == NULL) {
    DPDK_CHILD_LOG(DPDK_EVENTS_PLUGIN ": Invalid argument(phc)\n");
    return -EINVAL;
  }

  if (cmd != DPDK_CMD_GET_EVENTS) {
    DPDK_CHILD_LOG(DPDK_EVENTS_PLUGIN ": Unknown command (cmd=%d)\n", cmd);
    return -EINVAL;
  }

  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(phc);
  int ret = 0;
  if (ec->config.link_status.enabled)
    ret = dpdk_helper_link_status_get(phc);

  return ret;
}