int main(int argc, char **argv) {
  char address[1024];
  lcc_connection_t *connection;

  int status;

  range_critical_g.min = NAN;
  range_critical_g.max = NAN;
  range_critical_g.invert = 0;

  range_warning_g.min = NAN;
  range_warning_g.max = NAN;
  range_warning_g.invert = 0;

  while (42) {
    int c;

    c = getopt(argc, argv, "w:c:s:n:H:g:d:hm");
    if (c < 0)
      break;

    switch (c) {
    case 'c':
      parse_range(optarg, &range_critical_g);
      break;
    case 'w':
      parse_range(optarg, &range_warning_g);
      break;
    case 's':
      socket_file_g = optarg;
      break;
    case 'n':
      value_string_g = optarg;
      break;
    case 'H':
      hostname_g = optarg;
      break;
    case 'g':
      if (strcasecmp(optarg, "none") == 0)
        consolitation_g = CON_NONE;
      else if (strcasecmp(optarg, "average") == 0)
        consolitation_g = CON_AVERAGE;
      else if (strcasecmp(optarg, "sum") == 0)
        consolitation_g = CON_SUM;
      else if (strcasecmp(optarg, "percentage") == 0)
        consolitation_g = CON_PERCENTAGE;
      else {
        fprintf(stderr, "Unknown consolidation function `%s'.\n", optarg);
        usage(argv[0]);
      }
      break;
    case 'd': {
      char **tmp;
      tmp = realloc(match_ds_g, (match_ds_num_g + 1) * sizeof(char *));
      if (tmp == NULL) {
        fprintf(stderr, "realloc failed: %s\n", strerror(errno));
        return (RET_UNKNOWN);
      }
      match_ds_g = tmp;
      match_ds_g[match_ds_num_g] = cn_strdup(optarg);
      if (match_ds_g[match_ds_num_g] == NULL) {
        fprintf(stderr, "cn_strdup failed: %s\n", strerror(errno));
        return (RET_UNKNOWN);
      }
      match_ds_num_g++;
      break;
    }
    case 'm':
      nan_is_error_g = 1;
      break;
    default:
      usage(argv[0]);
    } /* switch (c) */
  }

  if ((socket_file_g == NULL) || (value_string_g == NULL) ||
      ((hostname_g == NULL) && (strcasecmp(value_string_g, "LIST")))) {
    fprintf(stderr, "Missing required arguments.\n");
    usage(argv[0]);
  }

  snprintf(address, sizeof(address), "unix:%s", socket_file_g);
  address[sizeof(address) - 1] = 0;

  connection = NULL;
  status = lcc_connect(address, &connection);
  if (status != 0) {
    printf("ERROR: Connecting to daemon at %s failed.\n", socket_file_g);
    return (RET_CRITICAL);
  }

  if (0 == strcasecmp(value_string_g, "LIST"))
    return (do_listval(connection));

  return (do_check(connection));
}