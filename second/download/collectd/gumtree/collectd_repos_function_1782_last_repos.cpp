static int dpdk_helper_exit_command(dpdk_helper_ctx_t *phc,
                                    enum DPDK_HELPER_STATUS status) {
  char errbuf[ERR_BUF_SIZE];
  DPDK_HELPER_TRACE(phc->shm_name);

  close(phc->pipes[1]);

  if (phc->status == DPDK_HELPER_ALIVE_SENDING_EVENTS) {
    phc->status = status;
    DEBUG("%s:%s:%d %s", phc->shm_name, __FUNCTION__, __LINE__,
          dpdk_helper_status_str(status));

    int ret = dpdk_helper_command(phc, DPDK_CMD_QUIT, NULL, 0);
    if (ret != 0) {
      DEBUG("%s:%s:%d kill helper (pid=%lu)", phc->shm_name, __FUNCTION__,
            __LINE__, (long)phc->pid);

      int err = kill(phc->pid, SIGKILL);
      if (err) {
        ERROR("%s error sending kill to helper: %s", __FUNCTION__,
              sstrerror(errno, errbuf, sizeof(errbuf)));
      }
    }
  } else {

    DEBUG("%s:%s:%d kill helper (pid=%lu)", phc->shm_name, __FUNCTION__,
          __LINE__, (long)phc->pid);

    int err = kill(phc->pid, SIGKILL);
    if (err) {
      ERROR("%s error sending kill to helper: %s", __FUNCTION__,
            sstrerror(errno, errbuf, sizeof(errbuf)));
    }
  }

  return 0;
}