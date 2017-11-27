int main(int argc, char **argv) {
  char address[1024] = "unix:" DEFAULT_SOCK;

  lcc_connection_t *c;

  int status;

  while (42) {
    int opt;

    opt = getopt(argc, argv, "s:h");

    if (opt == -1)
      break;

    switch (opt) {
    case 's':
      snprintf(address, sizeof(address), "unix:%s", optarg);
      address[sizeof(address) - 1] = '\0';
      break;
    case 'h':
      exit_usage(argv[0], 0);
    default:
      exit_usage(argv[0], 1);
    }
  }

  if (optind >= argc) {
    fprintf(stderr, "%s: missing command\n", argv[0]);
    exit_usage(argv[0], 1);
  }

  c = NULL;
  status = lcc_connect(address, &c);
  if (status != 0) {
    fprintf(stderr, "ERROR: Failed to connect to daemon at %s: %s.\n", address,
            strerror(errno));
    return 1;
  }

  if (strcasecmp(argv[optind], "getval") == 0)
    status = getval(c, argc - optind, argv + optind);
  else if (strcasecmp(argv[optind], "flush") == 0)
    status = flush(c, argc - optind, argv + optind);
  else if (strcasecmp(argv[optind], "listval") == 0)
    status = listval(c, argc - optind, argv + optind);
  else if (strcasecmp(argv[optind], "putval") == 0)
    status = putval(c, argc - optind, argv + optind);
  else {
    fprintf(stderr, "%s: invalid command: %s\n", argv[0], argv[optind]);
    return 1;
  }

  LCC_DESTROY(c);

  if (status != 0)
    return status;
  return 0;
}