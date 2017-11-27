static int dpdk_helper_status_check(dpdk_helper_ctx_t *phc) {
  DEBUG("%s:%s:%d pid=%u %s", phc->shm_name, __FUNCTION__, __LINE__, getpid(),
        dpdk_helper_status_str(phc->status));
  char errbuf[ERR_BUF_SIZE];

  if (phc->status == DPDK_HELPER_GRACEFUL_QUIT) {
    return 0;
  } else if (phc->status == DPDK_HELPER_NOT_INITIALIZED) {
    phc->status = DPDK_HELPER_INITIALIZING;
    DEBUG("%s:%s:%d DPDK_HELPER_INITIALIZING", phc->shm_name, __FUNCTION__,
          __LINE__);
    int err = dpdk_helper_spawn(phc);
    if (err) {
      ERROR("dpdkstat: error spawning helper %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    }
    return -1;
  }

  pid_t ws = waitpid(phc->pid, NULL, WNOHANG);
  if (ws != 0) {
    phc->status = DPDK_HELPER_INITIALIZING;
    DEBUG("%s:%s:%d DPDK_HELPER_INITIALIZING", phc->shm_name, __FUNCTION__,
          __LINE__);
    int err = dpdk_helper_spawn(phc);
    if (err) {
      ERROR("dpdkstat: error spawning helper %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
    }
    return -1;
  }

  if (phc->status == DPDK_HELPER_INITIALIZING_EAL) {
    return -1;
  }

  return 0;
}