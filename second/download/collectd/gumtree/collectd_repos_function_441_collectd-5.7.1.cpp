static void *us_handle_client(void *arg) {
  int fdin;
  int fdout;
  FILE *fhin, *fhout;

  fdin = *((int *)arg);
  free(arg);
  arg = NULL;

  DEBUG("unixsock plugin: us_handle_client: Reading from fd #%i", fdin);

  fdout = dup(fdin);
  if (fdout < 0) {
    char errbuf[1024];
    ERROR("unixsock plugin: dup failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    close(fdin);
    pthread_exit((void *)1);
  }

  fhin = fdopen(fdin, "r");
  if (fhin == NULL) {
    char errbuf[1024];
    ERROR("unixsock plugin: fdopen failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    close(fdin);
    close(fdout);
    pthread_exit((void *)1);
    return ((void *)1);
  }

  fhout = fdopen(fdout, "w");
  if (fhout == NULL) {
    char errbuf[1024];
    ERROR("unixsock plugin: fdopen failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    fclose(fhin); /* this closes fdin as well */
    close(fdout);
    pthread_exit((void *)1);
    return ((void *)1);
  }

  /* change output buffer to line buffered mode */
  if (setvbuf(fhout, NULL, _IOLBF, 0) != 0) {
    char errbuf[1024];
    ERROR("unixsock plugin: setvbuf failed: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    fclose(fhin);
    fclose(fhout);
    pthread_exit((void *)1);
    return ((void *)0);
  }

  while (42) {
    char buffer[1024];
    char buffer_copy[1024];
    char *fields[128];
    int fields_num;
    int len;

    errno = 0;
    if (fgets(buffer, sizeof(buffer), fhin) == NULL) {
      if ((errno == EINTR) || (errno == EAGAIN))
        continue;

      if (errno != 0) {
        char errbuf[1024];
        WARNING("unixsock plugin: failed to read from socket #%i: %s",
                fileno(fhin), sstrerror(errno, errbuf, sizeof(errbuf)));
      }
      break;
    }

    len = strlen(buffer);
    while ((len > 0) &&
           ((buffer[len - 1] == '\n') || (buffer[len - 1] == '\r')))
      buffer[--len] = '\0';

    if (len == 0)
      continue;

    sstrncpy(buffer_copy, buffer, sizeof(buffer_copy));

    fields_num =
        strsplit(buffer_copy, fields, sizeof(fields) / sizeof(fields[0]));
    if (fields_num < 1) {
      fprintf(fhout, "-1 Internal error\n");
      fclose(fhin);
      fclose(fhout);
      pthread_exit((void *)1);
      return ((void *)1);
    }

    if (strcasecmp(fields[0], "getval") == 0) {
      cmd_handle_getval(fhout, buffer);
    } else if (strcasecmp(fields[0], "getthreshold") == 0) {
      handle_getthreshold(fhout, buffer);
    } else if (strcasecmp(fields[0], "putval") == 0) {
      cmd_handle_putval(fhout, buffer);
    } else if (strcasecmp(fields[0], "listval") == 0) {
      cmd_handle_listval(fhout, buffer);
    } else if (strcasecmp(fields[0], "putnotif") == 0) {
      handle_putnotif(fhout, buffer);
    } else if (strcasecmp(fields[0], "flush") == 0) {
      cmd_handle_flush(fhout, buffer);
    } else {
      if (fprintf(fhout, "-1 Unknown command: %s\n", fields[0]) < 0) {
        char errbuf[1024];
        WARNING("unixsock plugin: failed to write to socket #%i: %s",
                fileno(fhout), sstrerror(errno, errbuf, sizeof(errbuf)));
        break;
      }
    }
  } /* while (fgets) */

  DEBUG("unixsock plugin: us_handle_client: Exiting..");
  fclose(fhin);
  fclose(fhout);

  pthread_exit((void *)0);
  return ((void *)0);
}