static int perform(CURLM *multi)
{
  int handles;
  fd_set fdread, fdwrite, fdexcep;
  int res = 0;

  for(;;) {
    struct timeval interval;
    int maxfd = -99;

    interval.tv_sec = 0;
    interval.tv_usec = 100000L; /* 100 ms */

    res_multi_perform(multi, &handles);
    if(res)
      return res;

    res_test_timedout();
    if(res)
      return res;

    if(!handles)
      break; /* done */

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    res_multi_fdset(multi, &fdread, &fdwrite, &fdexcep, &maxfd);
    if(res)
      return res;

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    res_select_test(maxfd+1, &fdread, &fdwrite, &fdexcep, &interval);
    if(res)
      return res;

    res_test_timedout();
    if(res)
      return res;
  }

  return 0; /* success */
}