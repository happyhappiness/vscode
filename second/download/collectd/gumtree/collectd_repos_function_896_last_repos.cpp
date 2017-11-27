static int memcached_read(user_data_t *user_data) {
  char buf[4096];
  char *fields[3];
  char *line;

  derive_t bytes_used = 0;
  derive_t bytes_total = 0;
  derive_t get_hits = 0;
  derive_t cmd_get = 0;
  derive_t incr_hits = 0;
  derive_t incr_misses = 0;
  derive_t decr_hits = 0;
  derive_t decr_misses = 0;
  derive_t rusage_user = 0;
  derive_t rusage_syst = 0;
  derive_t octets_rx = 0;
  derive_t octets_tx = 0;

  memcached_t *st = user_data->data;
  prev_t *prev = &st->prev;

  /* get data from daemon */
  if (memcached_query_daemon(buf, sizeof(buf), st) < 0) {
    return -1;
  }

#define FIELD_IS(cnst)                                                         \
  (((sizeof(cnst) - 1) == name_len) && (strcmp(cnst, fields[1]) == 0))

  char *ptr = buf;
  char *saveptr = NULL;
  while ((line = strtok_r(ptr, "\n\r", &saveptr)) != NULL) {
    ptr = NULL;

    if (strsplit(line, fields, 3) != 3)
      continue;

    int name_len = strlen(fields[1]);
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
      /* Convert to useconds */
      rusage_user = atof(fields[2]) * 1000000;
    } else if (FIELD_IS("rusage_system")) {
      rusage_syst = atof(fields[2]) * 1000000;
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
      bytes_used = atoll(fields[2]);
    } else if (FIELD_IS("limit_maxbytes")) {
      bytes_total = atoll(fields[2]);
    }

    /*
     * Connections
     */
    else if (FIELD_IS("curr_connections")) {
      submit_gauge("memcached_connections", "current", atof(fields[2]), st);
    } else if (FIELD_IS("listen_disabled_num")) {
      submit_derive("total_events", "listen_disabled", atoll(fields[2]), st);
    }
    /*
     * Total number of connections opened since the server started running
     * Report this as connection rate.
     */
    else if (FIELD_IS("total_connections")) {
      submit_derive("connections", "opened", atoll(fields[2]), st);
    }

    /*
     * Commands
     */
    else if ((name_len > 4) && (strncmp(fields[1], "cmd_", 4) == 0)) {
      const char *name = fields[1] + 4;
      submit_derive("memcached_command", name, atoll(fields[2]), st);
      if (strcmp(name, "get") == 0)
        cmd_get = atoll(fields[2]);
    }

    /*
     * Increment/Decrement
     */
    else if (FIELD_IS("incr_misses")) {
      incr_misses = atoll(fields[2]);
      submit_derive("memcached_ops", "incr_misses", incr_misses, st);
    } else if (FIELD_IS("incr_hits")) {
      incr_hits = atoll(fields[2]);
      submit_derive("memcached_ops", "incr_hits", incr_hits, st);
    } else if (FIELD_IS("decr_misses")) {
      decr_misses = atoll(fields[2]);
      submit_derive("memcached_ops", "decr_misses", decr_misses, st);
    } else if (FIELD_IS("decr_hits")) {
      decr_hits = atoll(fields[2]);
      submit_derive("memcached_ops", "decr_hits", decr_hits, st);
    }

    /*
     * Operations on the cache:
     * - get hits/misses
     * - delete hits/misses
     * - evictions
     */
    else if (FIELD_IS("get_hits")) {
      get_hits = atoll(fields[2]);
      submit_derive("memcached_ops", "hits", get_hits, st);
    } else if (FIELD_IS("get_misses")) {
      submit_derive("memcached_ops", "misses", atoll(fields[2]), st);
    } else if (FIELD_IS("evictions")) {
      submit_derive("memcached_ops", "evictions", atoll(fields[2]), st);
    } else if (FIELD_IS("delete_hits")) {
      submit_derive("memcached_ops", "delete_hits", atoll(fields[2]), st);
    } else if (FIELD_IS("delete_misses")) {
      submit_derive("memcached_ops", "delete_misses", atoll(fields[2]), st);
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

  if ((bytes_total > 0) && (bytes_used <= bytes_total))
    submit_gauge2("df", "cache", bytes_used, bytes_total - bytes_used, st);

  if ((rusage_user != 0) || (rusage_syst != 0))
    submit_derive2("ps_cputime", NULL, rusage_user, rusage_syst, st);

  if ((octets_rx != 0) || (octets_tx != 0))
    submit_derive2("memcached_octets", NULL, octets_rx, octets_tx, st);

  if ((cmd_get != 0) && (get_hits != 0)) {
    gauge_t ratio =
        calculate_ratio_percent(get_hits, cmd_get, &prev->hits, &prev->gets);
    submit_gauge("percent", "hitratio", ratio, st);
  }

  if ((incr_hits != 0) && (incr_misses != 0)) {
    gauge_t ratio = calculate_ratio_percent2(
        incr_hits, incr_misses, &prev->incr_hits, &prev->incr_misses);
    submit_gauge("percent", "incr_hitratio", ratio, st);
    submit_derive("memcached_ops", "incr", incr_hits + incr_misses, st);
  }

  if ((decr_hits != 0) && (decr_misses != 0)) {
    gauge_t ratio = calculate_ratio_percent2(
        decr_hits, decr_misses, &prev->decr_hits, &prev->decr_misses);
    submit_gauge("percent", "decr_hitratio", ratio, st);
    submit_derive("memcached_ops", "decr", decr_hits + decr_misses, st);
  }

  return 0;
}