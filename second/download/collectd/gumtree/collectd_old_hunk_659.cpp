      fclose(fhout);
      pthread_exit((void *)1);
      return ((void *)1);
    }

    if (strcasecmp(fields[0], "getval") == 0) {
      handle_getval(fhout, buffer);
    } else if (strcasecmp(fields[0], "getthreshold") == 0) {
      handle_getthreshold(fhout, buffer);
    } else if (strcasecmp(fields[0], "putval") == 0) {
      handle_putval(fhout, buffer);
    } else if (strcasecmp(fields[0], "listval") == 0) {
      handle_listval(fhout, buffer);
    } else if (strcasecmp(fields[0], "putnotif") == 0) {
      handle_putnotif(fhout, buffer);
    } else if (strcasecmp(fields[0], "flush") == 0) {
      handle_flush(fhout, buffer);
    } else {
      if (fprintf(fhout, "-1 Unknown command: %s\n", fields[0]) < 0) {
        char errbuf[1024];
        WARNING("unixsock plugin: failed to write to socket #%i: %s",
                fileno(fhout), sstrerror(errno, errbuf, sizeof(errbuf)));
        break;
