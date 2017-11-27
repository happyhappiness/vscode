static int memcached_read(user_data_t *user_data) {
  char buf[4096];
  char *fields[3];
  char *ptr;
  char *line;
  char *saveptr;
  int fields_num;

  gauge_t bytes_used = NAN;
  gauge_t bytes_total = NAN;
  gauge_t hits = NAN;
  gauge_t gets = NAN;
  gauge_t incr_hits = NAN;
  derive_t incr = 0;
  gauge_t decr_hits = NAN;
  derive_t decr = 0;
  derive_t rusage_user = 0;
  derive_t rusage_syst = 0;
  derive_t octets_rx = 0;
  derive_t octets_tx = 0;

  memcached_t *st;
  st = user_data->data;

  /* get data from daemon */
  if (memcached_query_daemon(buf, sizeof(buf), st) < 0) {
    return -1;
  }

#define FIELD_IS(cnst)                                                         \
  (((sizeof(cnst) - 1) == name_len) && (strcmp(cnst, fields[1]) == 0))

  ptr = buf;
  saveptr = NULL;
  while ((line = strtok_r(ptr, "\n\r", &saveptr)) != NULL) {
    int name_len;

    ptr = NULL;

    fields_num = strsplit(line, fields, 3);
    if (fields_num != 3)
      continue;

    name_len = strlen(fields[1]);
    if (name_len == 0)
      continue;

    /*
     * For an explanation on these fields please refer to
     * <https://github.com/memcached/memcached/blob/master/doc/protocol.txt>
     */

    /*
     * CPU time consumed by the memcached process
     */
    if (FIELD_IS("rusage_user")) {
      rusage_user = atoll(fields[2]);
    } else if (FIELD_IS("rusage_system")) {
      rusage_syst = atoll(fields[2]);
    }

    /*
     * Number of threads of this instance
     */
    else if (FIELD_IS("threads")) {
      submit_gauge2("ps_count", NULL, NAN, atof(fields[2]), st);
    }

    /*
     * Number of items stored
     */
    else if (FIELD_IS("curr_items")) {
      submit_gauge("memcached_items", "current", atof(fields[2]), st);
    }

    /*
     * Number of bytes used and available (total - used)
     */
    else if (FIELD_IS("bytes")) {
      bytes_used = atof(fields[2]);
    } else if (FIELD_IS("limit_maxbytes")) {
      bytes_total = atof(fields[2]);
    }

    /*
     * Connections
     */
    else if (FIELD_IS("curr_connections")) {
      submit_gauge("memcached_connections", "current", atof(fields[2]), st);
    } else if (FIELD_IS("listen_disabled_num")) {
      submit_derive("connections", "listen_disabled", atof(fields[2]), st);
    }

    /*
     * Commands
     */
    else if ((name_len > 4) && (strncmp(fields[1], "cmd_", 4) == 0)) {
      const char *name = fields[1] + 4;
      submit_derive("memcached_command", name, atoll(fields[2]), st);
      if (strcmp(name, "get") == 0)
        gets = atof(fields[2]);
    }

    /*
     * Increment/Decrement
     */
    else if (FIELD_IS("incr_misses")) {
      derive_t incr_count = atoll(fields[2]);
      submit_derive("memcached_ops", "incr_misses", incr_count, st);
      incr += incr_count;
    } else if (FIELD_IS("incr_hits")) {
      derive_t incr_count = atoll(fields[2]);
      submit_derive("memcached_ops", "incr_hits", incr_count, st);
      incr_hits = atof(fields[2]);
      incr += incr_count;
    } else if (FIELD_IS("decr_misses")) {
      derive_t decr_count = atoll(fields[2]);
      submit_derive("memcached_ops", "decr_misses", decr_count, st);
      decr += decr_count;
    } else if (FIELD_IS("decr_hits")) {
      derive_t decr_count = atoll(fields[2]);
      submit_derive("memcached_ops", "decr_hits", decr_count, st);
      decr_hits = atof(fields[2]);
      decr += decr_count;
    }

    /*
     * Operations on the cache, i. e. cache hits, cache misses and evictions of
     * items
     */
    else if (FIELD_IS("get_hits")) {
      submit_derive("memcached_ops", "hits", atoll(fields[2]), st);
      hits = atof(fields[2]);
    } else if (FIELD_IS("get_misses")) {
      submit_derive("memcached_ops", "misses", atoll(fields[2]), st);
    } else if (FIELD_IS("evictions")) {
      submit_derive("memcached_ops", "evictions", atoll(fields[2]), st);
    }

    /*
     * Network traffic
     */
    else if (FIELD_IS("bytes_read")) {
      octets_rx = atoll(fields[2]);
    } else if (FIELD_IS("bytes_written")) {
      octets_tx = atoll(fields[2]);
    }
  } /* while ((line = strtok_r (ptr, "\n\r", &saveptr)) != NULL) */

  if (!isnan(bytes_used) && !isnan(bytes_total) && (bytes_used <= bytes_total))
    submit_gauge2("df", "cache", bytes_used, bytes_total - bytes_used, st);

  if ((rusage_user != 0) || (rusage_syst != 0))
    submit_derive2("ps_cputime", NULL, rusage_user, rusage_syst, st);

  if ((octets_rx != 0) || (octets_tx != 0))
    submit_derive2("memcached_octets", NULL, octets_rx, octets_tx, st);

  if (!isnan(gets) && !isnan(hits)) {
    gauge_t rate = NAN;

    if (gets != 0.0)
      rate = 100.0 * hits / gets;

    submit_gauge("percent", "hitratio", rate, st);
  }

  if (!isnan(incr_hits) && incr != 0) {
    gauge_t incr_rate = 100.0 * incr_hits / incr;
    submit_gauge("percent", "incr_hitratio", incr_rate, st);
    submit_derive("memcached_ops", "incr", incr, st);
  }

  if (!isnan(decr_hits) && decr != 0) {
    gauge_t decr_rate = 100.0 * decr_hits / decr;
    submit_gauge("percent", "decr_hitratio", decr_rate, st);
    submit_derive("memcached_ops", "decr", decr, st);
  }

  return 0;
}