static int dpdk_helper_exit(dpdk_helper_ctx_t *phc,
                            enum DPDK_HELPER_STATUS status) {
  DPDK_CHILD_LOG("%s:%s:%d %s\n", phc->shm_name, __FUNCTION__, __LINE__,
                 dpdk_helper_status_str(status));

  close(phc->pipes[1]);

  phc->status = status;

  exit(0);

  return 0;
}