static int collectd_start(char **argv) {
  pid_t pid = 0;

  if (0 > (pid = fork())) {
    syslog(LOG_ERR, "Error: fork() failed: %s", strerror(errno));
    return -1;
  } else if (pid != 0) {
    collectd_pid = pid;
    return 0;
  }

  execvp(argv[0], argv);
  syslog(LOG_ERR, "Error: execvp(%s) failed: %s", argv[0], strerror(errno));
  exit(-1);
}