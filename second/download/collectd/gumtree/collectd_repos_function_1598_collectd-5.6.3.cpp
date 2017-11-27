static void statsd_parse_buffer(char *buffer) /* {{{ */
{
  while (buffer != NULL) {
    char orig[64];
    char *next;
    int status;

    next = strchr(buffer, '\n');
    if (next != NULL) {
      *next = 0;
      next++;
    }

    if (*buffer == 0) {
      buffer = next;
      continue;
    }

    sstrncpy(orig, buffer, sizeof(orig));

    status = statsd_parse_line(buffer);
    if (status != 0)
      ERROR("statsd plugin: Unable to parse line: \"%s\"", orig);

    buffer = next;
  }
}