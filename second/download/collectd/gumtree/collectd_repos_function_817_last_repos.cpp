static void log_logstash_print(yajl_gen g, int severity,
                               cdtime_t timestamp_time) {
  FILE *fh;
  _Bool do_close = 0;
  struct tm timestamp_tm;
  char timestamp_str[64];
  const unsigned char *buf;
#if HAVE_YAJL_V2
  size_t len;
#else
  unsigned int len;
#endif

  if (yajl_gen_string(g, (u_char *)"level", strlen("level")) !=
      yajl_gen_status_ok)
    goto err;

  switch (severity) {
  case LOG_ERR:
    if (yajl_gen_string(g, (u_char *)"error", strlen("error")) !=
        yajl_gen_status_ok)
      goto err;
    break;
  case LOG_WARNING:
    if (yajl_gen_string(g, (u_char *)"warning", strlen("warning")) !=
        yajl_gen_status_ok)
      goto err;
    break;
  case LOG_NOTICE:
    if (yajl_gen_string(g, (u_char *)"notice", strlen("notice")) !=
        yajl_gen_status_ok)
      goto err;
    break;
  case LOG_INFO:
    if (yajl_gen_string(g, (u_char *)"info", strlen("info")) !=
        yajl_gen_status_ok)
      goto err;
    break;
  case LOG_DEBUG:
    if (yajl_gen_string(g, (u_char *)"debug", strlen("debug")) !=
        yajl_gen_status_ok)
      goto err;
    break;
  default:
    if (yajl_gen_string(g, (u_char *)"unknown", strlen("unknown")) !=
        yajl_gen_status_ok)
      goto err;
    break;
  }

  if (yajl_gen_string(g, (u_char *)"@timestamp", strlen("@timestamp")) !=
      yajl_gen_status_ok)
    goto err;

  gmtime_r(&CDTIME_T_TO_TIME_T(timestamp_time), &timestamp_tm);

  /*
   * format time as a UTC ISO 8601 compliant string
   */
  strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%dT%H:%M:%SZ",
           &timestamp_tm);
  timestamp_str[sizeof(timestamp_str) - 1] = '\0';

  if (yajl_gen_string(g, (u_char *)timestamp_str, strlen(timestamp_str)) !=
      yajl_gen_status_ok)
    goto err;

  if (yajl_gen_map_close(g) != yajl_gen_status_ok)
    goto err;

  if (yajl_gen_get_buf(g, &buf, &len) != yajl_gen_status_ok)
    goto err;
  pthread_mutex_lock(&file_lock);

  if (log_file == NULL) {
    fh = stderr;
  } else if (strcasecmp(log_file, "stdout") == 0) {
    fh = stdout;
    do_close = 0;
  } else if (strcasecmp(log_file, "stderr") == 0) {
    fh = stderr;
    do_close = 0;
  } else {
    fh = fopen(log_file, "a");
    do_close = 1;
  }

  if (fh == NULL) {
    char errbuf[1024];
    fprintf(stderr, "log_logstash plugin: fopen (%s) failed: %s\n", log_file,
            sstrerror(errno, errbuf, sizeof(errbuf)));
  } else {
    fprintf(fh, "%s\n", buf);
    if (do_close) {
      fclose(fh);
    } else {
      fflush(fh);
    }
  }
  pthread_mutex_unlock(&file_lock);
  yajl_gen_free(g);
  return;

err:
  yajl_gen_free(g);
  fprintf(stderr, "Could not correctly generate JSON message\n");
  return;
}