               );

    if (c == -1)
      break;

    switch (c) {
    case 'B':
      config->create_basedir = 0;
      break;
    case 'C':
      config->configfile = optarg;
      break;
    case 't':
      config->test_config = 1;
      break;
    case 'T':
      config->test_readall = 1;
      global_option_set("ReadThreads", "-1", 1);
#if COLLECT_DAEMON
      config->daemonize = 0;
#endif /* COLLECT_DAEMON */
      break;
#if COLLECT_DAEMON
    case 'P':
      global_option_set("PIDFile", optarg, 1);
      break;
    case 'f':
      config->daemonize = 0;
      break;
#endif /* COLLECT_DAEMON */
    case 'h':
      exit_usage(0);
      break;
    default:
      exit_usage(1);
    } /* switch (c) */
  }   /* while (1) */
}

int configure_collectd(struct cmdline_config *config) {
  const char *basedir;
  /*
   * Read options from the config file, the environment and the command
   * line (in that order, with later options overwriting previous ones in
   * general).
   * Also, this will automatically load modules.
   */
  if (cf_read(config->configfile)) {
    fprintf(stderr, "Error: Reading the config file failed!\n"
                    "Read the logs for details.\n");
    return 1;
  }

  /*
   * Change directory. We do this _after_ reading the config and loading
   * modules to relative paths work as expected.
   */
  if ((basedir = global_option_get("BaseDir")) == NULL) {
    fprintf(stderr,
            "Don't have a basedir to use. This should not happen. Ever.");
    return 1;
  } else if (change_basedir(basedir, config->create_basedir)) {
    fprintf(stderr, "Error: Unable to change to directory `%s'.\n", basedir);
    return 1;
  }

  /*
   * Set global variables or, if that fails, exit. We cannot run with
   * them being uninitialized. If nothing is configured, then defaults
   * are being used. So this means that the user has actually done
   * something wrong.
   */
  if (init_global_variables() != 0)
    return 1;

  return 0;
}

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
