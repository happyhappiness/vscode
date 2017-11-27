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
