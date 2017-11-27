int main(int argc, char **argv) {
#if COLLECT_DAEMON
  pid_t pid;
#endif
  int exit_status = 0;

  struct cmdline_config config = {
      .daemonize = 1, .create_basedir = 1, .configfile = CONFIGFILE,
  };

  read_cmdline(argc, argv, &config);

  if (config.test_config)
    return 0;

  if (optind < argc)
    exit_usage(1);

  plugin_init_ctx();

  int status;
  if ((status = configure_collectd(&config)) != 0)
    exit(EXIT_FAILURE);

#if COLLECT_DAEMON
  /*
   * fork off child
   */
  struct sigaction sig_chld_action = {.sa_handler = SIG_IGN};

  sigaction(SIGCHLD, &sig_chld_action, NULL);

  /*
   * Only daemonize if we're not being supervised
   * by upstart or systemd (when using Linux).
   */
  if (config.daemonize
#ifdef KERNEL_LINUX
      && notify_upstart() == 0 && notify_systemd() == 0
#endif
      ) {
    int status;

    if ((pid = fork()) == -1) {
      /* error */
      char errbuf[1024];
      fprintf(stderr, "fork: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
      return 1;
    } else if (pid != 0) {
      /* parent */
      /* printf ("Running (PID %i)\n", pid); */
      return 0;
    }

    /* Detach from session */
    setsid();

    /* Write pidfile */
    if (pidfile_create())
      exit(2);

    /* close standard descriptors */
    close(2);
    close(1);
    close(0);

    status = open("/dev/null", O_RDWR);
    if (status != 0) {
      ERROR("Error: Could not connect `STDIN' to `/dev/null' (status %d)",
            status);
      return 1;
    }

    status = dup(0);
    if (status != 1) {
      ERROR("Error: Could not connect `STDOUT' to `/dev/null' (status %d)",
            status);
      return 1;
    }

    status = dup(0);
    if (status != 2) {
      ERROR("Error: Could not connect `STDERR' to `/dev/null', (status %d)",
            status);
      return 1;
    }
  }    /* if (config.daemonize) */
#endif /* COLLECT_DAEMON */

  struct sigaction sig_pipe_action = {.sa_handler = SIG_IGN};

  sigaction(SIGPIPE, &sig_pipe_action, NULL);

  /*
   * install signal handlers
   */
  struct sigaction sig_int_action = {.sa_handler = sig_int_handler};

  if (0 != sigaction(SIGINT, &sig_int_action, NULL)) {
    char errbuf[1024];
    ERROR("Error: Failed to install a signal handler for signal INT: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  struct sigaction sig_term_action = {.sa_handler = sig_term_handler};

  if (0 != sigaction(SIGTERM, &sig_term_action, NULL)) {
    char errbuf[1024];
    ERROR("Error: Failed to install a signal handler for signal TERM: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  struct sigaction sig_usr1_action = {.sa_handler = sig_usr1_handler};

  if (0 != sigaction(SIGUSR1, &sig_usr1_action, NULL)) {
    char errbuf[1024];
    ERROR("Error: Failed to install a signal handler for signal USR1: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  /*
   * run the actual loops
   */
  if (do_init() != 0) {
    ERROR("Error: one or more plugin init callbacks failed.");
    exit_status = 1;
  }

  if (config.test_readall) {
    if (plugin_read_all_once() != 0) {
      ERROR("Error: one or more plugin read callbacks failed.");
      exit_status = 1;
    }
  } else {
    INFO("Initialization complete, entering read-loop.");
    do_loop();
  }

  /* close syslog */
  INFO("Exiting normally.");

  if (do_shutdown() != 0) {
    ERROR("Error: one or more plugin shutdown callbacks failed.");
    exit_status = 1;
  }

#if COLLECT_DAEMON
  if (config.daemonize)
    pidfile_remove();
#endif /* COLLECT_DAEMON */

  return exit_status;
}