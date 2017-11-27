static int cj_sock_perform(cj_t *db) /* {{{ */
{
  char errbuf[1024];
  struct sockaddr_un sa_unix = {0};
  sa_unix.sun_family = AF_UNIX;
  sstrncpy(sa_unix.sun_path, db->sock, sizeof(sa_unix.sun_path));

  int fd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (fd < 0)
    return (-1);
  if (connect(fd, (struct sockaddr *)&sa_unix, sizeof(sa_unix)) < 0) {
    ERROR("curl_json plugin: connect(%s) failed: %s",
          (db->sock != NULL) ? db->sock : "<null>",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    close(fd);
    return (-1);
  }

  ssize_t red;
  do {
    unsigned char buffer[4096];
    red = read(fd, buffer, sizeof(buffer));
    if (red < 0) {
      ERROR("curl_json plugin: read(%s) failed: %s",
            (db->sock != NULL) ? db->sock : "<null>",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      close(fd);
      return (-1);
    }
    if (!cj_curl_callback(buffer, red, 1, db))
      break;
  } while (red > 0);
  close(fd);
  return (0);
}