FILE *fopen(const char *path, const char *mode) {
  char filename[BUFSIZE] = "\0";

  FILE *(*original_fopen)(const char *, const char *);
  original_fopen = dlsym(RTLD_NEXT, "fopen");

  return (*original_fopen)(add_prefix(path, filename), mode);
}