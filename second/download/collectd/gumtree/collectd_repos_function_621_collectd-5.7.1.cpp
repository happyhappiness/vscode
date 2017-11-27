static int my_asprintf(char **str, const char *fmt, ...) {
  int size = 0;
  va_list args;
  // init variadic argumens
  va_start(args, fmt);
  // format and get size
  size = my_vasprintf(str, fmt, args);
  // toss args
  va_end(args);
  return size;
}