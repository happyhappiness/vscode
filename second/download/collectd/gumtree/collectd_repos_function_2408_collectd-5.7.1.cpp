static int lcc_tracef(char const *format,
                                                            ...) {
  va_list ap;
  int status;

  char const *trace = getenv(LCC_TRACE_ENV);
  if (!trace || (strcmp("", trace) == 0) || (strcmp("0", trace) == 0))
    return 0;

  va_start(ap, format);
  status = vprintf(format, ap);
  va_end(ap);

  return status;
}