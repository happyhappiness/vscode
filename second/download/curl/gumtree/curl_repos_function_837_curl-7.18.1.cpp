int Curl_socket_ready(curl_socket_t readfd, curl_socket_t writefd,
                      int timeout_ms)
{
#ifdef HAVE_POLL_FINE
  struct pollfd pfd[2];
  int num;
#else
  struct timeval pending_tv;
  struct timeval *ptimeout;
  fd_set fds_read;
  fd_set fds_write;
  fd_set fds_err;
  curl_socket_t maxfd;
#endif
  struct timeval initial_tv = {0,0};
  int pending_ms = 0;
  int error;
  int r;
  int ret;

  if((readfd == CURL_SOCKET_BAD) && (writefd == CURL_SOCKET_BAD)) {
    r = wait_ms(timeout_ms);
    return r;
  }

  /* Avoid initial timestamp, avoid gettimeofday() call, when elapsed
     time in this function does not need to be measured. This happens
     when function is called with a zero timeout or a negative timeout
     value indicating a blocking call should be performed. */

  if(timeout_ms > 0) {
    pending_ms = timeout_ms;
    initial_tv = curlx_tvnow();
  }

#ifdef HAVE_POLL_FINE

  num = 0;
  if(readfd != CURL_SOCKET_BAD) {
    pfd[num].fd = readfd;
    pfd[num].events = POLLRDNORM|POLLIN|POLLRDBAND|POLLPRI;
    pfd[num].revents = 0;
    num++;
  }
  if(writefd != CURL_SOCKET_BAD) {
    pfd[num].fd = writefd;
    pfd[num].events = POLLWRNORM|POLLOUT;
    pfd[num].revents = 0;
    num++;
  }

  do {
    if(timeout_ms < 0)
      pending_ms = -1;
    else if(!timeout_ms)
      pending_ms = 0;
    r = poll(pfd, num, pending_ms);
    if(r != -1)
      break;
    error = SOCKERRNO;
    if(error && error_not_EINTR)
      break;
    if(timeout_ms > 0) {
      pending_ms = timeout_ms - elapsed_ms;
      if(pending_ms <= 0)
        break;
    }
  } while(r == -1);

  if(r < 0)
    return -1;
  if(r == 0)
    return 0;

  ret = 0;
  num = 0;
  if(readfd != CURL_SOCKET_BAD) {
    if(pfd[num].revents & (POLLRDNORM|POLLIN|POLLERR|POLLHUP))
      ret |= CURL_CSELECT_IN;
    if(pfd[num].revents & (POLLRDBAND|POLLPRI|POLLNVAL))
      ret |= CURL_CSELECT_ERR;
    num++;
  }
  if(writefd != CURL_SOCKET_BAD) {
    if(pfd[num].revents & (POLLWRNORM|POLLOUT))
      ret |= CURL_CSELECT_OUT;
    if(pfd[num].revents & (POLLERR|POLLHUP|POLLNVAL))
      ret |= CURL_CSELECT_ERR;
  }

  return ret;

#else  /* HAVE_POLL_FINE */

  FD_ZERO(&fds_err);
  maxfd = (curl_socket_t)-1;

  FD_ZERO(&fds_read);
  if(readfd != CURL_SOCKET_BAD) {
    VERIFY_SOCK(readfd);
    FD_SET(readfd, &fds_read);
    FD_SET(readfd, &fds_err);
    maxfd = readfd;
  }

  FD_ZERO(&fds_write);
  if(writefd != CURL_SOCKET_BAD) {
    VERIFY_SOCK(writefd);
    FD_SET(writefd, &fds_write);
    FD_SET(writefd, &fds_err);
    if(writefd > maxfd)
      maxfd = writefd;
  }

  ptimeout = (timeout_ms < 0) ? NULL : &pending_tv;

  do {
    if(timeout_ms > 0) {
      pending_tv.tv_sec = pending_ms / 1000;
      pending_tv.tv_usec = (pending_ms % 1000) * 1000;
    }
    else if(!timeout_ms) {
      pending_tv.tv_sec = 0;
      pending_tv.tv_usec = 0;
    }
    r = select((int)maxfd + 1, &fds_read, &fds_write, &fds_err, ptimeout);
    if(r != -1)
      break;
    error = SOCKERRNO;
    if(error && error_not_EINTR)
      break;
    if(timeout_ms > 0) {
      pending_ms = timeout_ms - elapsed_ms;
      if(pending_ms <= 0)
        break;
    }
  } while(r == -1);

  if(r < 0)
    return -1;
  if(r == 0)
    return 0;

  ret = 0;
  if(readfd != CURL_SOCKET_BAD) {
    if(FD_ISSET(readfd, &fds_read))
      ret |= CURL_CSELECT_IN;
    if(FD_ISSET(readfd, &fds_err))
      ret |= CURL_CSELECT_ERR;
  }
  if(writefd != CURL_SOCKET_BAD) {
    if(FD_ISSET(writefd, &fds_write))
      ret |= CURL_CSELECT_OUT;
    if(FD_ISSET(writefd, &fds_err))
      ret |= CURL_CSELECT_ERR;
  }

  return ret;

#endif  /* HAVE_POLL_FINE */

}