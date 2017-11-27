int *open(const char *pathname, int flags) {
  char filename[BUFSIZE] = "\0";

  int *(*original_open)(const char *, int);
  original_open = dlsym(RTLD_NEXT, "open");

  return (*original_open)(add_prefix(pathname, filename), flags);
}