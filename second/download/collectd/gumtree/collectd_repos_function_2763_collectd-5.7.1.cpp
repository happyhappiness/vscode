int parse_log_severity(const char *severity) {
  int log_level = -1;

  if ((0 == strcasecmp(severity, "emerg")) ||
      (0 == strcasecmp(severity, "alert")) ||
      (0 == strcasecmp(severity, "crit")) || (0 == strcasecmp(severity, "err")))
    log_level = LOG_ERR;
  else if (0 == strcasecmp(severity, "warning"))
    log_level = LOG_WARNING;
  else if (0 == strcasecmp(severity, "notice"))
    log_level = LOG_NOTICE;
  else if (0 == strcasecmp(severity, "info"))
    log_level = LOG_INFO;
#if COLLECT_DEBUG
  else if (0 == strcasecmp(severity, "debug"))
    log_level = LOG_DEBUG;
#endif /* COLLECT_DEBUG */

  return (log_level);
}