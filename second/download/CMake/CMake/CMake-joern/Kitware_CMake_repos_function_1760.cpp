static int uv__makedir_p(const char *dir) {
  char tmp[256];
  char *p = NULL;
  size_t len;
  int err;

  snprintf(tmp, sizeof(tmp),"%s",dir);
  len = strlen(tmp);
  if (tmp[len - 1] == '/')
    tmp[len - 1] = 0;
  for (p = tmp + 1; *p; p++) {
    if (*p == '/') {
      *p = 0;
      err = mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
      if (err != 0 && errno != EEXIST)
        return err;
      *p = '/';
    }
  }
  return mkdir(tmp, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}