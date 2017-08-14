static int uv__make_subdirs_p(const char *filename) {
  char cmd[2048];
  char *p;
  int rc = 0;

  /* Strip off the monitor file name */
  p = strrchr(filename, '/');

  if (p == NULL)
    return 0;

  if (uv__path_is_a_directory((char*)filename) == 0) {
    sprintf(cmd, "/aha/fs/modDir.monFactory");
  } else {
    sprintf(cmd, "/aha/fs/modFile.monFactory");
  }

  strncat(cmd, filename, (p - filename));
  rc = uv__makedir_p(cmd);

  if (rc == -1 && errno != EEXIST){
    return -errno;
  }

  return rc;
}