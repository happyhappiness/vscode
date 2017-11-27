static int sl_config(const char *key, const char *value) {
  if (strcasecmp(key, "LogLevel") == 0) {
    log_level = parse_log_severity(value);
    if (log_level < 0) {
      log_level = LOG_INFO;
      ERROR("syslog: invalid loglevel [%s] defaulting to 'info'", value);
      return 1;
    }
  } else if (strcasecmp(key, "NotifyLevel") == 0) {
    notif_severity = parse_notif_severity(value);
    if (notif_severity < 0)
      return 1;
  }

  return 0;
}