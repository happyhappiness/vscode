static int dpdk_events_shutdown(void) {
  DPDK_EVENTS_TRACE();

  if (g_hc == NULL)
    return 0;

  dpdk_events_ctx_t *ec = DPDK_EVENTS_CTX_GET(g_hc);
  if (ec->config.keep_alive.enabled) {
    if (ec->config.keep_alive.fd != -1) {
      close(ec->config.keep_alive.fd);
      ec->config.keep_alive.fd = -1;
    }

    if (ec->config.keep_alive.shm != MAP_FAILED) {
      if (munmap(ec->config.keep_alive.shm, sizeof(dpdk_keepalive_shm_t))) {
        ERROR(DPDK_EVENTS_PLUGIN ": munmap KA monitor failed");
        return -1;
      }
      ec->config.keep_alive.shm = MAP_FAILED;
    }
  }

  dpdk_helper_shutdown(g_hc);
  g_hc = NULL;

  return 0;
}