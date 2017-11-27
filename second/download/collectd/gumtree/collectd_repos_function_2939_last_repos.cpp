const char *add_prefix(const char *orig, char *prefixed) {
  if ((strncmp(orig, "/proc", strlen("/proc")) != 0) &&
      (strncmp(orig, "/sys", strlen("/sys")) != 0))
    return orig;

  int status = snprintf(prefixed, BUFSIZE, "%s%s", PREFIX, orig);
  if (status < 1) {
    error(status, errno, "adding '%s' prefix to file path failed: '%s' -> '%s'",
          PREFIX, orig, prefixed);
    return orig;
  } else if ((unsigned int)status >= BUFSIZE) {
    error(status, ENAMETOOLONG,
          "'%s' got truncated when adding '%s' prefix: '%s'", orig, PREFIX,
          prefixed);
    return orig;
  } else {
    return (const char *)prefixed;
  }
}