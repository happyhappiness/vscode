static int dpdk_shm_cleanup(void) {
  int ret = munmap(g_configuration, sizeof(dpdk_config_t));
  g_configuration = 0;
  if (ret) {
    ERROR("dpdkstat: munmap returned %d", ret);
    return ret;
  }
  ret = shm_unlink(DPDK_SHM_NAME);
  if (ret) {
    ERROR("dpdkstat: shm_unlink returned %d", ret);
    return ret;
  }
  return 0;
}