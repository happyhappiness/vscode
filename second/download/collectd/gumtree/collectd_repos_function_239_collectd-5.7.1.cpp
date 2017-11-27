static int dpdk_init(void) {
  int err = dpdk_shm_init(sizeof(dpdk_config_t));
  if (err) {
    ERROR("dpdkstat: %s : error %d in shm_init()", __func__, err);
    return err;
  }

  /* If the XML config() function has been run, dont re-initialize defaults */
  if (!g_configured) {
    dpdk_config_init_default();
  }

  return 0;
}