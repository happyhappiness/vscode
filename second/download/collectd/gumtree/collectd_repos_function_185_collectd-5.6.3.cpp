static int apache_read_host(user_data_t *user_data) /* {{{ */
{
  char *ptr;
  char *saveptr;
  char *line;

  char *fields[4];
  int fields_num;

  apache_t *st;

  st = user_data->data;

  int status;

  char *content_type;
  static const char *text_plain = "text/plain";

  assert(st->url != NULL);
  /* (Assured by `config_add') */

  if (st->curl == NULL) {
    status = init_host(st);
    if (status != 0)
      return (-1);
  }
  assert(st->curl != NULL);

  st->apache_buffer_fill = 0;

  curl_easy_setopt(st->curl, CURLOPT_URL, st->url);

  if (curl_easy_perform(st->curl) != CURLE_OK) {
    ERROR("apache: curl_easy_perform failed: %s", st->apache_curl_error);
    return (-1);
  }

  /* fallback - server_type to apache if not set at this time */
  if (st->server_type == -1) {
    WARNING("apache plugin: Unable to determine server software "
            "automatically. Will assume Apache.");
    st->server_type = APACHE;
  }

  status = curl_easy_getinfo(st->curl, CURLINFO_CONTENT_TYPE, &content_type);
  if ((status == CURLE_OK) && (content_type != NULL) &&
      (strncasecmp(content_type, text_plain, strlen(text_plain)) != 0)) {
    WARNING("apache plugin: `Content-Type' response header is not `%s' "
            "(received: `%s'). Expecting unparseable data. Please check `URL' "
            "parameter (missing `?auto' suffix ?)",
            text_plain, content_type);
  }

  ptr = st->apache_buffer;
  saveptr = NULL;
  while ((line = strtok_r(ptr, "\n\r", &saveptr)) != NULL) {
    ptr = NULL;
    fields_num = strsplit(line, fields, STATIC_ARRAY_SIZE(fields));

    if (fields_num == 3) {
      if ((strcmp(fields[0], "Total") == 0) &&
          (strcmp(fields[1], "Accesses:") == 0))
        submit_derive("apache_requests", "", atoll(fields[2]), st);
      else if ((strcmp(fields[0], "Total") == 0) &&
               (strcmp(fields[1], "kBytes:") == 0))
        submit_derive("apache_bytes", "", 1024LL * atoll(fields[2]), st);
    } else if (fields_num == 2) {
      if (strcmp(fields[0], "Scoreboard:") == 0)
        submit_scoreboard(fields[1], st);
      else if ((strcmp(fields[0], "BusyServers:") == 0) /* Apache 1.* */
               || (strcmp(fields[0], "BusyWorkers:") == 0) /* Apache 2.* */)
        submit_gauge("apache_connections", NULL, atol(fields[1]), st);
      else if ((strcmp(fields[0], "IdleServers:") == 0) /* Apache 1.x */
               || (strcmp(fields[0], "IdleWorkers:") == 0) /* Apache 2.x */)
        submit_gauge("apache_idle_workers", NULL, atol(fields[1]), st);
    }
  }

  st->apache_buffer_fill = 0;

  return (0);
}