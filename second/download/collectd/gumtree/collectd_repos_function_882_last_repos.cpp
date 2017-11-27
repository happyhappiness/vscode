static int synproxy_read(void) {
  char buf[1024];
  value_t results[SYNPROXY_FIELDS];
  int is_header = 1, status = 0;

  FILE *fh = fopen(synproxy_stat_path, "r");
  if (fh == NULL) {
    ERROR("synproxy plugin: unable to open %s", synproxy_stat_path);
    return -1;
  }

  memset(results, 0, sizeof(results));

  while (fgets(buf, sizeof(buf), fh) != NULL) {
    char *fields[SYNPROXY_FIELDS], *endprt;

    if (is_header) {
      is_header = 0;
      continue;
    }

    int numfields = strsplit(buf, fields, STATIC_ARRAY_SIZE(fields));
    if (numfields != SYNPROXY_FIELDS) {
      ERROR("synproxy plugin: unexpected number of columns in %s",
            synproxy_stat_path);
      status = -1;
      break;
    }

    /* 1st column (entries) is hardcoded to 0 in kernel code */
    for (size_t n = 1; n < SYNPROXY_FIELDS; n++) {
      char *endptr = NULL;
      errno = 0;

      results[n].derive += strtoull(fields[n], &endprt, 16);
      if ((endptr == fields[n]) || errno != 0) {
        ERROR("synproxy plugin: unable to parse value: %s", fields[n]);
        fclose(fh);
        return -1;
      }
    }
  }

  fclose(fh);

  if (status == 0) {
    synproxy_submit(results);
  }

  return status;
}