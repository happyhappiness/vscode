int dpdk_helper_command(dpdk_helper_ctx_t *phc, enum DPDK_CMD cmd, int *result,
                        cdtime_t cmd_wait_time) {
  if (phc == NULL) {
    ERROR("Invalid argument(phc)");
    return -EINVAL;
  }

  DEBUG("%s:%s:%d pid=%lu, cmd=%d", phc->shm_name, __FUNCTION__, __LINE__,
        (long)getpid(), cmd);

  phc->cmd_wait_time = cmd_wait_time;

  int ret = dpdk_helper_status_check(phc);

  dpdk_helper_check_pipe(phc);

  if (ret != 0) {
    return ret;
  }

  DEBUG("%s: DPDK command execute (cmd=%d)", phc->shm_name, cmd);

  phc->cmd_result = 0;
  phc->cmd = cmd;

  /* kick helper to process command */
  int err = sem_post(&phc->sema_cmd_start);
  if (err) {
    char errbuf[ERR_BUF_SIZE];
    ERROR("dpdk_helper_worker: error posting sema_cmd_start semaphore (%s)",
          sstrerror(errno, errbuf, sizeof(errbuf)));
  }

#if COLLECT_DEBUG
  int val = 0;
  if (sem_getvalue(&phc->sema_cmd_start, &val) == 0)
    DEBUG("%s:dpdk_helper_command: post sema_cmd_start (value=%d)",
          phc->shm_name, val);
#endif

  if (phc->cmd != DPDK_CMD_QUIT) {

    /* wait for helper to complete processing */
    struct timespec ts;
    cdtime_t now = cdtime();

    if (phc->status != DPDK_HELPER_ALIVE_SENDING_EVENTS) {
      cmd_wait_time = MS_TO_CDTIME_T(DPDK_CDM_DEFAULT_TIMEOUT);
    }

    ts = CDTIME_T_TO_TIMESPEC(now + cmd_wait_time);
    ret = sem_timedwait(&phc->sema_cmd_complete, &ts);
    if (ret == -1 && errno == ETIMEDOUT) {
      DPDK_HELPER_TRACE(phc->shm_name);
      DEBUG("%s:sema_cmd_start: timeout in collectd thread: is a DPDK Primary "
            "running?",
            phc->shm_name);
      return -ETIMEDOUT;
    }

#if COLLECT_DEBUG
    val = 0;
    if (sem_getvalue(&phc->sema_cmd_complete, &val) == 0)
      DEBUG("%s:dpdk_helper_command: wait sema_cmd_complete (value=%d)",
            phc->shm_name, val);
#endif

    if (result) {
      *result = phc->cmd_result;
    }
  }

  dpdk_helper_check_pipe(phc);

  DEBUG("%s: DPDK command complete (cmd=%d, result=%d)", phc->shm_name,
        phc->cmd, phc->cmd_result);

  return 0;
}