static int logfile_config(const char *key, const char *value) {
  if (0 == strcasecmp(key, "LogLevel")) {
    log_level = parse_log_severity(value);
    if (log_level < 0) {
      log_level = LOG_INFO;
      ERROR("logfile: invalid loglevel [%s] defaulting to 'info'", value);
      return (1);
    }
  } else if (0 == strcasecmp(key, "File")) {
    sfree(log_file);
    log_file = strdup(value);
  } else if (0 == strcasecmp(key, "Timestamp")) {
    if (IS_FALSE(value))
      print_timestamp = 0;
    else
      print_timestamp = 1;
  } else if (0 == strcasecmp(key, "PrintSeverity")) {
    if (IS_FALSE(value))
      print_severity = 0;
    else
      print_severity = 1;
  } else {
    return -1;
  }
  return 0;
}