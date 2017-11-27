DIR *opendir(const char *name) {
  char filename[BUFSIZE] = "\0";

  DIR *(*original_opendir)(const char *);
  original_opendir = dlsym(RTLD_NEXT, "opendir");

  return (*original_opendir)(add_prefix(name, filename));
}