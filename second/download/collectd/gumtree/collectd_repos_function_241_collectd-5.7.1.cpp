static int dpdk_helper_spawn(enum DPDK_HELPER_ACTION action) {
  char errbuf[ERR_BUF_SIZE];
  g_configuration->eal_initialized = 0;
  g_configuration->helper_action = action;
  /*
   * Create a pipe for helper stdout back to collectd. This is necessary for
   * logging EAL failures, as rte_eal_init() calls rte_panic().
   */
  if (pipe(g_configuration->helper_pipes) != 0) {
    DEBUG("dpdkstat: Could not create helper pipe: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  int pipe0_flags = fcntl(g_configuration->helper_pipes[0], F_GETFL, 0);
  int pipe1_flags = fcntl(g_configuration->helper_pipes[1], F_GETFL, 0);
  if (pipe0_flags == -1 || pipe1_flags == -1) {
    WARNING("dpdkstat: Failed setting up pipe flags: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
  }
  int pipe0_err = fcntl(g_configuration->helper_pipes[0], F_SETFL,
                        pipe1_flags | O_NONBLOCK);
  int pipe1_err = fcntl(g_configuration->helper_pipes[1], F_SETFL,
                        pipe0_flags | O_NONBLOCK);
  if (pipe0_err == -1 || pipe1_err == -1) {
    WARNING("dpdkstat: Failed setting up pipes: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
  }

  pid_t pid = fork();
  if (pid > 0) {
    close(g_configuration->helper_pipes[1]);
    g_configuration->helper_pid = pid;
    DEBUG("dpdkstat: helper pid %li", (long)g_configuration->helper_pid);
    /* Kick helper once its alive to have it start processing */
    sem_post(&g_configuration->sema_helper_get_stats);
  } else if (pid == 0) {
    /* Replace stdout with a pipe to collectd. */
    close(g_configuration->helper_pipes[0]);
    close(STDOUT_FILENO);
    dup2(g_configuration->helper_pipes[1], STDOUT_FILENO);
    dpdk_helper_run();
    exit(0);
  } else {
    ERROR("dpdkstat: Failed to fork helper process: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }
  return 0;
}