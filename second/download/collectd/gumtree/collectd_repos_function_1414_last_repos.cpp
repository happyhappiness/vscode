static int fhcount_read(void) {
  int numfields = 0;
  int buffer_len = 60;
  gauge_t used, unused, max;
  int prc_used, prc_unused;
  char *fields[3];
  char buffer[buffer_len];
  char errbuf[1024];
  FILE *fp;

  // Open file
  fp = fopen("/proc/sys/fs/file-nr", "r");
  if (fp == NULL) {
    ERROR("fhcount: fopen: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
    return EXIT_FAILURE;
  }
  if (fgets(buffer, buffer_len, fp) == NULL) {
    ERROR("fhcount: fgets: %s", sstrerror(errno, errbuf, sizeof(errbuf)));
    fclose(fp);
    return EXIT_FAILURE;
  }
  fclose(fp);

  // Tokenize string
  numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));

  if (numfields != 3) {
    ERROR("fhcount: Line doesn't contain 3 fields");
    return EXIT_FAILURE;
  }

  // Define the values
  strtogauge(fields[0], &used);
  strtogauge(fields[1], &unused);
  strtogauge(fields[2], &max);
  prc_used = (gauge_t)used / max * 100;
  prc_unused = (gauge_t)unused / max * 100;

  // Submit values
  if (values_absolute) {
    fhcount_submit("file_handles", "used", (gauge_t)used);
    fhcount_submit("file_handles", "unused", (gauge_t)unused);
    fhcount_submit("file_handles", "max", (gauge_t)max);
  }
  if (values_percentage) {
    fhcount_submit("percent", "used", (gauge_t)prc_used);
    fhcount_submit("percent", "unused", (gauge_t)prc_unused);
  }

  return 0;
}