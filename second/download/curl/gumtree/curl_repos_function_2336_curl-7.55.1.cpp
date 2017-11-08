static int pipe_ssloverssl(struct connectdata *conn, int sockindex,
                           int directions)
{
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  struct ssl_connect_data *connproxyssl = &conn->proxy_ssl[sockindex];
  fd_set fds_read;
  fd_set fds_write;
  int n;
  int m;
  int i;
  int ret = 0;
  struct timeval tv = {0, 0};
  char buf[CURL_MAX_WRITE_SIZE];

  if(!connssl->use || !connproxyssl->use)
    return 0;   /* No SSL over SSL: OK. */

  FD_ZERO(&fds_read);
  FD_ZERO(&fds_write);
  n = -1;
  if(directions & SOS_READ) {
    FD_SET(connssl->remotefd, &fds_write);
    n = connssl->remotefd;
  }
  if(directions & SOS_WRITE) {
    FD_SET(connssl->remotefd, &fds_read);
    n = connssl->remotefd;
    FD_SET(conn->sock[sockindex], &fds_write);
    if(n < conn->sock[sockindex])
      n = conn->sock[sockindex];
  }
  i = select(n + 1, &fds_read, &fds_write, NULL, &tv);
  if(i < 0)
    return -1;  /* Select error. */

  if(FD_ISSET(connssl->remotefd, &fds_write)) {
    /* Try getting data from HTTPS proxy and pipe it upstream. */
    n = 0;
    i = gsk_secure_soc_read(connproxyssl->handle, buf, sizeof buf, &n);
    switch(i) {
    case GSK_OK:
      if(n) {
        i = write(connssl->remotefd, buf, n);
        if(i < 0)
          return -1;
        ret = 1;
      }
      break;
    case GSK_OS400_ERROR_TIMED_OUT:
    case GSK_WOULD_BLOCK:
      break;
    default:
      return -1;
    }
  }

  if(FD_ISSET(connssl->remotefd, &fds_read) &&
     FD_ISSET(conn->sock[sockindex], &fds_write)) {
    /* Pipe data to HTTPS proxy. */
    n = read(connssl->remotefd, buf, sizeof buf);
    if(n < 0)
      return -1;
    if(n) {
      i = gsk_secure_soc_write(connproxyssl->handle, buf, n, &m);
      if(i != GSK_OK || n != m)
        return -1;
      ret = 1;
    }
  }

  return ret;  /* OK */
}