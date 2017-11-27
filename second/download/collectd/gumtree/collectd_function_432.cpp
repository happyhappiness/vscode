static void logfile_print(const char *msg, int severity,
                          cdtime_t timestamp_time) {
  FILE *fh;
  _Bool do_close = 0;
  struct tm timestamp_tm;
  char timestamp_str[64];
  char level_str[16] = "";

  if (print_severity) {
    switch (severity) {
    case LOG_ERR:
      snprintf(level_str, sizeof(level_str), "[error] ");
      break;
    case LOG_WARNING:
      snprintf(level_str, sizeof(level_str), "[warning] ");
      break;
    case LOG_NOTICE:
      snprintf(level_str, sizeof(level_str), "[notice] ");
      break;
    case LOG_INFO:
      snprintf(level_str, sizeof(level_str), "[info] ");
      break;
    case LOG_DEBUG:
      snprintf(level_str, sizeof(level_str), "[debug] ");
      break;
    default:
      break;
    }
  }

  if (print_timestamp) {
    time_t tt = CDTIME_T_TO_TIME_T(timestamp_time);
    localtime_r(&tt, &timestamp_tm);

    strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S",
             &timestamp_tm);
    timestamp_str[sizeof(timestamp_str) - 1] = '\0';
  }

  pthread_mutex_lock(&file_lock);

  if (log_file == NULL) {
    fh = stderr;
  } else if (strcasecmp(log_file, "stderr") == 0)
    fh = stderr;
  else if (strcasecmp(log_file, "stdout") == 0)
    fh = stdout;
  else {
    fh = fopen(log_file, "a");
    do_close = 1;
  }

  if (fh == NULL) {
    char errbuf[1024];
    fprintf(stderr, "logfile plugin: fopen (%s) failed: %s\n", log_file,
            sstrerror(errno, errbuf, sizeof(errbuf)));
  } else {
    if (print_timestamp)
      fprintf(fh, "[%s] %s%s\n", timestamp_str, level_str, msg);
    else
      fprintf(fh, "%s%s\n", level_str, msg);

    if (do_close) {
      fclose(fh);
    } else {
      fflush(fh);
    }
  }

  pthread_mutex_unlock(&file_lock);

  return;
}