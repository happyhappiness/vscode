static int loop(CURLM *cm, const char* url, const char* userpwd,
                struct curl_slist *headers)
{
  CURLMsg *msg;
  long L;
  int M, Q, U = -1;
  fd_set R, W, E;
  struct timeval T;

  init(cm, url, userpwd, headers);

  while (U) {
    while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(cm, &U));

    if (U) {
      FD_ZERO(&R);
      FD_ZERO(&W);
      FD_ZERO(&E);

      if (curl_multi_fdset(cm, &R, &W, &E, &M)) {
        fprintf(stderr, "E: curl_multi_fdset\n");
        return EXIT_FAILURE;
      }

      /* In a real-world program you OF COURSE check the return that maxfd is
         bigger than -1 so that the call to select() below makes sense! */

      if (curl_multi_timeout(cm, &L)) {
        fprintf(stderr, "E: curl_multi_timeout\n");
        return EXIT_FAILURE;
      }

      if(L != -1) {
        T.tv_sec = L/1000;
        T.tv_usec = (L%1000)*1000;
      }
      else {
        T.tv_sec = 5;
        T.tv_usec = 0;
      }

      if (0 > select(M+1, &R, &W, &E, &T)) {
        fprintf(stderr, "E: select\n");
        return EXIT_FAILURE;
      }
    }

    while ((msg = curl_multi_info_read(cm, &Q))) {
      if (msg->msg == CURLMSG_DONE) {
        CURL *e = msg->easy_handle;
        fprintf(stderr, "R: %d - %s\n", (int)msg->data.result,
                curl_easy_strerror(msg->data.result));
        curl_multi_remove_handle(cm, e);
        curl_easy_cleanup(e);
      }
      else {
        fprintf(stderr, "E: CURLMsg (%d)\n", (int)msg->msg);
      }
    }
  }

  return 1;
}