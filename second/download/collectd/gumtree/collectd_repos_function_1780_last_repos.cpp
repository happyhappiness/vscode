static int dpdk_helper_spawn(dpdk_helper_ctx_t *phc) {
  char errbuf[ERR_BUF_SIZE];
  if (phc == NULL) {
    ERROR("Invalid argument(phc)");
    return -EINVAL;
  }

  DPDK_HELPER_TRACE(phc->shm_name);

  phc->eal_initialized = 0;
  phc->cmd_wait_time = MS_TO_CDTIME_T(DPDK_CDM_DEFAULT_TIMEOUT);

  /*
   * Create a pipe for helper stdout back to collectd. This is necessary for
   * logging EAL failures, as rte_eal_init() calls rte_panic().
   */
  if (phc->pipes[1]) {
    DEBUG("dpdk_helper_spawn: collectd closing helper pipe %d", phc->pipes[1]);
  } else {
    DEBUG("dpdk_helper_spawn: collectd helper pipe %d, not closing",
          phc->pipes[1]);
  }

  if (pipe(phc->pipes) != 0) {
    DEBUG("dpdk_helper_spawn: Could not create helper pipe: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  int pipe0_flags = fcntl(phc->pipes[0], F_GETFL, 0);
  int pipe1_flags = fcntl(phc->pipes[1], F_GETFL, 0);
  if (pipe0_flags == -1 || pipe1_flags == -1) {
    WARNING("dpdk_helper_spawn: error setting up pipe flags: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
  }
  int pipe0_err = fcntl(phc->pipes[0], F_SETFL, pipe1_flags | O_NONBLOCK);
  int pipe1_err = fcntl(phc->pipes[1], F_SETFL, pipe0_flags | O_NONBLOCK);
  if (pipe0_err == -1 || pipe1_err == -1) {
    WARNING("dpdk_helper_spawn: error setting up pipes: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
  }

  pid_t pid = fork();
  if (pid > 0) {
    phc->pid = pid;
    close(phc->pipes[1]);
    DEBUG("%s:dpdk_helper_spawn: helper pid %lu", phc->shm_name,
          (long)phc->pid);
  } else if (pid == 0) {
    /* Replace stdout with a pipe to collectd. */
    close(phc->pipes[0]);
    close(STDOUT_FILENO);
    dup2(phc->pipes[1], STDOUT_FILENO);
    DPDK_CHILD_TRACE(phc->shm_name);
    dpdk_helper_worker(phc);
    exit(0);
  } else {
    ERROR("dpdk_helper_start: Failed to fork helper process: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  return 0;
}