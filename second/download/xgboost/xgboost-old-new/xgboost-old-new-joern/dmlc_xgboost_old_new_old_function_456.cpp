inline void Assert(bool exp, const char *fmt, ...) {
  if (!exp) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "AssertError:");
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(-1);
  }
}