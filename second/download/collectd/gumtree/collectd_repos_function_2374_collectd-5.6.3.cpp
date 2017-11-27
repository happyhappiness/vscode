int ssnprintf(char *dest, size_t n, const char *format, ...) {
  int ret = 0;
  va_list ap;

  va_start(ap, format);
  ret = vsnprintf(dest, n, format, ap);
  dest[n - 1] = '\0';
  va_end(ap);

  return (ret);
}