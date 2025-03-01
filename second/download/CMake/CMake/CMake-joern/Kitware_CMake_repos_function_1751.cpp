int snprintf(char* buf, size_t len, const char* fmt, ...) {
  int n;
  va_list ap;
  va_start(ap, fmt);

  n = _vscprintf(fmt, ap);
  vsnprintf_s(buf, len, _TRUNCATE, fmt, ap);

  va_end(ap);
  return n;
}