int Curl_poll(struct pollfd ufds[], unsigned int nfds, int timeout_ms)
{
  int r;
#ifdef HAVE_POLL_FINE
  do {
    r = poll(ufds, nfds, timeout_ms);
  } while((r == -1) && (errno == EINTR));
#else
  struct timeval timeout;
  struct timeval *ptimeout;
  fd_set fds_read;
  fd_set fds_write;
  fd_set fds_err;
  curl_socket_t maxfd;
  unsigned int i;

  FD_ZERO(&fds_read);
  FD_ZERO(&fds_write);
  FD_ZERO(&fds_err);
  maxfd = -1;

  for (i = 0; i < nfds; i++) {
    if (ufds[i].fd == CURL_SOCKET_BAD)
      continue;
#ifndef WIN32  /* This is harmless and wrong on Win32 */
    if (ufds[i].fd >= FD_SETSIZE) {
      errno = EINVAL;
      return -1;
    }
#endif
    if (ufds[i].fd > maxfd)
      maxfd = ufds[i].fd;
    if (ufds[i].events & POLLIN)
      FD_SET(ufds[i].fd, &fds_read);
    if (ufds[i].events & POLLOUT)
      FD_SET(ufds[i].fd, &fds_write);
    if (ufds[i].events & POLLERR)
      FD_SET(ufds[i].fd, &fds_err);
  }

  if (timeout_ms < 0) {
    ptimeout = NULL;      /* wait forever */
  } else {
    timeout.tv_sec = timeout_ms / 1000;
    timeout.tv_usec = (timeout_ms % 1000) * 1000;
    ptimeout = &timeout;
  }

  do {
    r = select((int)maxfd + 1, &fds_read, &fds_write, &fds_err, ptimeout);
  } while((r == -1) && (Curl_ourerrno() == EINTR));

  if (r < 0)
    return -1;
  if (r == 0)
    return 0;

  r = 0;
  for (i = 0; i < nfds; i++) {
    ufds[i].revents = 0;
    if (ufds[i].fd == CURL_SOCKET_BAD)
      continue;
    if (FD_ISSET(ufds[i].fd, &fds_read))
      ufds[i].revents |= POLLIN;
    if (FD_ISSET(ufds[i].fd, &fds_write))
      ufds[i].revents |= POLLOUT;
    if (FD_ISSET(ufds[i].fd, &fds_err))
      ufds[i].revents |= POLLERR;
    if (ufds[i].revents != 0)
      r++;
  }
#endif
  return r;
}