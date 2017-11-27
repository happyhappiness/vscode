static int lcc_open_unixsocket(lcc_connection_t *c, const char *path) /* {{{ */
{
  struct sockaddr_un sa = {0};
  int fd;
  int status;

  assert(c != NULL);
  assert(c->fh == NULL);
  assert(path != NULL);

  /* Don't use PF_UNIX here, because it's broken on Mac OS X (10.4, possibly
   * others). */
  fd = socket(AF_UNIX, SOCK_STREAM, /* protocol = */ 0);
  if (fd < 0) {
    lcc_set_errno(c, errno);
    return -1;
  }

  sa.sun_family = AF_UNIX;
  strncpy(sa.sun_path, path, sizeof(sa.sun_path) - 1);

  status = connect(fd, (struct sockaddr *)&sa, sizeof(sa));
  if (status != 0) {
    lcc_set_errno(c, errno);
    close(fd);
    return -1;
  }

  c->fh = fdopen(fd, "r+");
  if (c->fh == NULL) {
    lcc_set_errno(c, errno);
    close(fd);
    return -1;
  }

  return 0;
}