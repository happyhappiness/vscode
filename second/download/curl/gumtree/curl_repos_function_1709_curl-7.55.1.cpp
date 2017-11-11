static int waitperform(struct connectdata *conn, int timeout_ms)
{
  struct Curl_easy *data = conn->data;
  int nfds;
  int bitmask;
  ares_socket_t socks[ARES_GETSOCK_MAXNUM];
  struct pollfd pfd[ARES_GETSOCK_MAXNUM];
  int i;
  int num = 0;

  bitmask = ares_getsock((ares_channel)data->state.resolver, socks,
                         ARES_GETSOCK_MAXNUM);

  for(i=0; i < ARES_GETSOCK_MAXNUM; i++) {
    pfd[i].events = 0;
    pfd[i].revents = 0;
    if(ARES_GETSOCK_READABLE(bitmask, i)) {
      pfd[i].fd = socks[i];
      pfd[i].events |= POLLRDNORM|POLLIN;
    }
    if(ARES_GETSOCK_WRITABLE(bitmask, i)) {
      pfd[i].fd = socks[i];
      pfd[i].events |= POLLWRNORM|POLLOUT;
    }
    if(pfd[i].events != 0)
      num++;
    else
      break;
  }

  if(num)
    nfds = Curl_poll(pfd, num, timeout_ms);
  else
    nfds = 0;

  if(!nfds)
    /* Call ares_process() unconditonally here, even if we simply timed out
       above, as otherwise the ares name resolve won't timeout! */
    ares_process_fd((ares_channel)data->state.resolver, ARES_SOCKET_BAD,
                    ARES_SOCKET_BAD);
  else {
    /* move through the descriptors and ask for processing on them */
    for(i=0; i < num; i++)
      ares_process_fd((ares_channel)data->state.resolver,
                      pfd[i].revents & (POLLRDNORM|POLLIN)?
                      pfd[i].fd:ARES_SOCKET_BAD,
                      pfd[i].revents & (POLLWRNORM|POLLOUT)?
                      pfd[i].fd:ARES_SOCKET_BAD);
  }
  return nfds;
}