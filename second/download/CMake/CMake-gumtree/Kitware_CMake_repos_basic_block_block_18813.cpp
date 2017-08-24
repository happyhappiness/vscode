{
  uv_passwd_t pwd;
  char* buf;
  size_t len;
  int r;

  if (buffer == NULL || size == NULL || *size == 0)
    return -EINVAL;

  /* Check if the HOME environment variable is set first */
  buf = getenv("HOME");

  if (buf != NULL) {
    len = strlen(buf);

    if (len >= *size) {
      *size = len + 1;
      return -ENOBUFS;
    }

    memcpy(buffer, buf, len + 1);
    *size = len;

    return 0;
  }

  /* HOME is not set, so call uv__getpwuid_r() */
  r = uv__getpwuid_r(&pwd);

  if (r != 0) {
    return r;
  }

  len = strlen(pwd.homedir);

  if (len >= *size) {
    *size = len + 1;
    uv_os_free_passwd(&pwd);
    return -ENOBUFS;
  }

  memcpy(buffer, pwd.homedir, len + 1);
  *size = len;
  uv_os_free_passwd(&pwd);

  return 0;
}