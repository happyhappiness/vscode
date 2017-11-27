static void *collect(void *arg) {
  collector_t *this = (collector_t *)arg;

  while (1) {
    conn_t *connection;

    pthread_mutex_lock(&conns_mutex);

    while (NULL == conns.head) {
      pthread_cond_wait(&conn_available, &conns_mutex);
    }

    connection = conns.head;
    conns.head = conns.head->next;

    if (NULL == conns.head) {
      conns.tail = NULL;
    }

    pthread_mutex_unlock(&conns_mutex);

    /* make the socket available to the global
     * thread and connection management */
    this->socket = connection->socket;

    log_debug("collect: handling connection on fd #%i", fileno(this->socket));

    while (42) {
      /* 256 bytes ought to be enough for anybody ;-) */
      char line[256 + 1]; /* line + '\0' */
      int len = 0;

      errno = 0;
      if (NULL == fgets(line, sizeof(line), this->socket)) {
        if (0 != errno) {
          char errbuf[1024];
          log_err("collect: reading from socket (fd #%i) "
                  "failed: %s",
                  fileno(this->socket),
                  sstrerror(errno, errbuf, sizeof(errbuf)));
        }
        break;
      }

      len = strlen(line);
      if (('\n' != line[len - 1]) && ('\r' != line[len - 1])) {
        log_warn("collect: line too long (> %zu characters): "
                 "'%s' (truncated)",
                 sizeof(line) - 1, line);

        while (NULL != fgets(line, sizeof(line), this->socket))
          if (('\n' == line[len - 1]) || ('\r' == line[len - 1]))
            break;
        continue;
      }
      if (len < 3) { /* [a-z] ':' '\n' */
        continue;
      }

      line[len - 1] = 0;

      log_debug("collect: line = '%s'", line);

      if (':' != line[1]) {
        log_err("collect: syntax error in line '%s'", line);
        continue;
      }

      if ('e' == line[0]) { /* e:<type>:<bytes> */
        char *ptr = NULL;
        char *type = strtok_r(line + 2, ":", &ptr);
        char *tmp = strtok_r(NULL, ":", &ptr);
        int bytes = 0;

        if (NULL == tmp) {
          log_err("collect: syntax error in line '%s'", line);
          continue;
        }

        bytes = atoi(tmp);

        pthread_mutex_lock(&count_mutex);
        type_list_incr(&list_count, type, /* increment = */ 1);
        pthread_mutex_unlock(&count_mutex);

        if (bytes > 0) {
          pthread_mutex_lock(&size_mutex);
          type_list_incr(&list_size, type, /* increment = */ bytes);
          pthread_mutex_unlock(&size_mutex);
        }
      } else if ('s' == line[0]) { /* s:<value> */
        pthread_mutex_lock(&score_mutex);
        score = (score * (double)score_count + atof(line + 2)) /
                (double)(score_count + 1);
        ++score_count;
        pthread_mutex_unlock(&score_mutex);
      } else if ('c' == line[0]) { /* c:<type1>[,<type2>,...] */
        char *dummy = line + 2;
        char *endptr = NULL;
        char *type;

        pthread_mutex_lock(&check_mutex);
        while ((type = strtok_r(dummy, ",", &endptr)) != NULL) {
          dummy = NULL;
          type_list_incr(&list_check, type, /* increment = */ 1);
        }
        pthread_mutex_unlock(&check_mutex);
      } else {
        log_err("collect: unknown type '%c'", line[0]);
      }
    } /* while (42) */

    log_debug("Shutting down connection on fd #%i", fileno(this->socket));

    fclose(connection->socket);
    free(connection);

    this->socket = NULL;

    pthread_mutex_lock(&available_mutex);
    ++available_collectors;
    pthread_mutex_unlock(&available_mutex);

    pthread_cond_signal(&collector_available);
  } /* while (1) */

  pthread_exit((void *)0);
  return ((void *)0);
}