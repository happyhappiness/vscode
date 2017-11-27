void read_cmdline(int argc, char **argv, struct cmdline_config *config) {
  /* read options */
  while (1) {
    int c;
    c = getopt(argc, argv, "htTC:"
#if COLLECT_DAEMON
                           "fP:"
#endif
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