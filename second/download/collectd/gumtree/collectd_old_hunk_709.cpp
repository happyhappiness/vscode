  sigaction(SIGCHLD, &sig_chld_action, NULL);

  /*
   * Only daemonize if we're not being supervised
   * by upstart or systemd (when using Linux).
   */
  if (daemonize
#ifdef KERNEL_LINUX
      && notify_upstart() == 0 && notify_systemd() == 0
#endif
      ) {
    int status;

    if ((pid = fork()) == -1) {
      /* error */
      char errbuf[1024];
      fprintf(stderr, "fork: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
      return (1);
    } else if (pid != 0) {
      /* parent */
      /* printf ("Running (PID %i)\n", pid); */
      return (0);
    }

    /* Detach from session */
    setsid();

    /* Write pidfile */
