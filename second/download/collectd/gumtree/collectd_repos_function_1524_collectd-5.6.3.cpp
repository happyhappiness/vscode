static int read_options(int argc, char **argv) /* {{{ */
{
  int opt;

  while ((opt = getopt(argc, argv, "n:H:p:i:d:D:h")) != -1) {
    switch (opt) {
    case 'n':
      get_integer_opt(optarg, &conf_num_values);
      break;

    case 'H':
      get_integer_opt(optarg, &conf_num_hosts);
      break;

    case 'p':
      get_integer_opt(optarg, &conf_num_plugins);
      break;

    case 'i':
      get_double_opt(optarg, &conf_interval);
      break;

    case 'd':
      conf_destination = optarg;
      break;

    case 'D':
      conf_service = optarg;
      break;

    case 'h':
      exit_usage(EXIT_SUCCESS);

    default:
      exit_usage(EXIT_FAILURE);
    } /* switch (opt) */
  }   /* while (getopt) */

  return (0);
}