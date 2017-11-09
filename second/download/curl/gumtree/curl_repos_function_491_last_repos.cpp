static int loop(int num, CURLM *cm, const char *url, const char *userpwd,
                struct curl_slist *headers)
{
  CURLMsg *msg;
  long L;
  int Q, U = -1;
  fd_set R, W, E;
  struct timeval T;
  int res = 0;

  res = init(num, cm, url, userpwd, headers);
  if(res)
    return res;

  while(U) {

    int M = -99;

    res_multi_perform(cm, &U);
    if(res)
      return res;

    res_test_timedout();
    if(res)
      return res;

    if(U) {
      FD_ZERO(&R);
      FD_ZERO(&W);
      FD_ZERO(&E);

      res_multi_fdset(cm, &R, &W, &E, &M);
      if(res)
        return res;

      /* At this point, M is guaranteed to be greater or equal than -1. */

      res_multi_timeout(cm, &L);
      if(res)
        return res;

      /* At this point, L is guaranteed to be greater or equal than -1. */

      if(L != -1) {
        int itimeout = (L > (long)INT_MAX) ? INT_MAX : (int)L;
        T.tv_sec = itimeout/1000;
        T.tv_usec = (itimeout%1000)*1000;
      }
      else {
        T.tv_sec = 5;
        T.tv_usec = 0;
      }

      res_select_test(M + 1, &R, &W, &E, &T);
      if(res)
        return res;
    }

    while((msg = curl_multi_info_read(cm, &Q)) != NULL) {
      if(msg->msg == CURLMSG_DONE) {
        int i;
        CURL *e = msg->easy_handle;
        fprintf(stderr, "R: %d - %s\n", (int)msg->data.result,
                curl_easy_strerror(msg->data.result));
        curl_multi_remove_handle(cm, e);
        curl_easy_cleanup(e);
        for(i = 0; i < NUM_HANDLES; i++) {
          if(eh[i] == e) {
            eh[i] = NULL;
            break;
          }
        }
      }
      else
        fprintf(stderr, "E: CURLMsg (%d)\n", (int)msg->msg);
    }

    res_test_timedout();
    if(res)
      return res;
  }

  return 0; /* success */
}