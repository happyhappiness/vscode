int Curl_resolver_getsock(struct connectdata *conn,
                          curl_socket_t *socks,
                          int numsocks)

{
  struct timeval maxtime;
  struct timeval timebuf;
  struct timeval *timeout;
  long milli;
  int max = ares_getsock((ares_channel)conn->data->state.resolver,
                         (ares_socket_t *)socks, numsocks);

  maxtime.tv_sec = CURL_TIMEOUT_RESOLVE;
  maxtime.tv_usec = 0;

  timeout = ares_timeout((ares_channel)conn->data->state.resolver, &maxtime,
                         &timebuf);
  milli = (timeout->tv_sec * 1000) + (timeout->tv_usec/1000);
  if(milli == 0)
    milli += 10;
  Curl_expire_latest(conn->data, milli);

  return max;
}