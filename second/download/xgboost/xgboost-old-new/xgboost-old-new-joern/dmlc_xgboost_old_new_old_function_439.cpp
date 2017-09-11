inline void Check(bool exp, const char *fmt, ...) {
  if (!exp) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(-1);
  }
}