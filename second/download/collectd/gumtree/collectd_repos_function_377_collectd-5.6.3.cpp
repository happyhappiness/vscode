static int apc_query_server(char const *node, char const *service,
                            apc_detail_t *apcups_detail) {
  int n;
  char recvline[1024];
  char *tokptr;
  char *toksaveptr;
  _Bool retry = 1;
  int status;

#if APCMAIN
#define PRINT_VALUE(name, val)                                                 \
  printf("  Found property: name = %s; value = %f;\n", name, val)
#else
#define PRINT_VALUE(name, val) /**/
#endif

  while (retry) {
    if (global_sockfd < 0) {
      global_sockfd = net_open(node, service);
      if (global_sockfd < 0) {
        ERROR("apcups plugin: Connecting to the "
              "apcupsd failed.");
        return (-1);
      }
    }

    status = net_send(&global_sockfd, "status", strlen("status"));
    if (status != 0) {
      /* net_send is closing the socket on error. */
      assert(global_sockfd < 0);
      if (retry) {
        retry = 0;
        count_retries++;
        continue;
      }

      ERROR("apcups plugin: Writing to the socket failed.");
      return (-1);
    }

    break;
  } /* while (retry) */

  /* When collectd's collection interval is larger than apcupsd's
   * timeout, we would have to retry / re-connect each iteration. Try to
   * detect this situation and shut down the socket gracefully in that
   * case. Otherwise, keep the socket open to avoid overhead. */
  count_iterations++;
  if ((count_iterations == 10) && (count_retries > 2)) {
    NOTICE("apcups plugin: There have been %i retries in the "
           "first %i iterations. Will close the socket "
           "in future iterations.",
           count_retries, count_iterations);
    conf_persistent_conn = 0;
  }

  while ((n = net_recv(&global_sockfd, recvline, sizeof(recvline) - 1)) > 0) {
    assert((size_t)n < sizeof(recvline));
    recvline[n] = 0;
#if APCMAIN
    printf("net_recv = `%s';\n", recvline);
#endif /* if APCMAIN */

    toksaveptr = NULL;
    tokptr = strtok_r(recvline, " :\t", &toksaveptr);
    while (tokptr != NULL) {
      char *key = tokptr;
      if ((tokptr = strtok_r(NULL, " :\t", &toksaveptr)) == NULL)
        continue;

      gauge_t value;
      if (strtogauge(tokptr, &value) != 0)
        continue;

      PRINT_VALUE(key, value);

      if (strcmp("LINEV", key) == 0)
        apcups_detail->linev = value;
      else if (strcmp("BATTV", key) == 0)
        apcups_detail->battv = value;
      else if (strcmp("ITEMP", key) == 0)
        apcups_detail->itemp = value;
      else if (strcmp("LOADPCT", key) == 0)
        apcups_detail->loadpct = value;
      else if (strcmp("BCHARGE", key) == 0)
        apcups_detail->bcharge = value;
      else if (strcmp("OUTPUTV", key) == 0)
        apcups_detail->outputv = value;
      else if (strcmp("LINEFREQ", key) == 0)
        apcups_detail->linefreq = value;
      else if (strcmp("TIMELEFT", key) == 0) {
        /* Convert minutes to seconds if requested by
         * the user. */
        if (conf_report_seconds)
          value *= 60.0;
        apcups_detail->timeleft = value;
      }

      tokptr = strtok_r(NULL, ":", &toksaveptr);
    } /* while (tokptr != NULL) */
  }
  status = errno; /* save errno, net_shutdown() may re-set it. */

  if (!conf_persistent_conn)
    net_shutdown(&global_sockfd);

  if (n < 0) {
    char errbuf[1024];
    ERROR("apcups plugin: Reading from socket failed: %s",
          sstrerror(status, errbuf, sizeof(errbuf)));
    return (-1);
  }

  return (0);
}