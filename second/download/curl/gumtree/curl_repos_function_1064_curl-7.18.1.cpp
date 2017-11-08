int Curl_resolv_getsock(struct connectdata *conn,
                        curl_socket_t *socks,
                        int numsocks)

{
  struct timeval maxtime;
  struct timeval timebuf;
  struct timeval *timeout;
  int max = ares_getsock(conn->data->state.areschannel,
                         (int *)socks, numsocks);


  maxtime.tv_sec = CURL_TIMEOUT_RESOLVE;
  maxtime.tv_usec = 0;

  timeout = ares_timeout(conn->data->state.areschannel, &maxtime, &timebuf);

  Curl_expire(conn->data,
              (timeout->tv_sec * 1000) + (timeout->tv_usec/1000));

  return max;
}