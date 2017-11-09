int main(void)
{
  CURLM *cm;
  CURLMsg *msg;
  long L;
  unsigned int C = 0;
  int M, Q, U = -1;
  fd_set R, W, E;
  struct timeval T;

  curl_global_init(CURL_GLOBAL_ALL);

  cm = curl_multi_init();

  /* we can optionally limit the total amount of connections this multi handle
     uses */
  curl_multi_setopt(cm, CURLMOPT_MAXCONNECTS, (long)MAX);

  for(C = 0; C < MAX; ++C) {
    init(cm, C);
  }

  while(U) {
    curl_multi_perform(cm, &U);

    if(U) {
      FD_ZERO(&R);
      FD_ZERO(&W);
      FD_ZERO(&E);

      if(curl_multi_fdset(cm, &R, &W, &E, &M)) {
        fprintf(stderr, "E: curl_multi_fdset\n");
        return EXIT_FAILURE;
      }

      if(curl_multi_timeout(cm, &L)) {
        fprintf(stderr, "E: curl_multi_timeout\n");
        return EXIT_FAILURE;
      }
      if(L == -1)
        L = 100;

      if(M == -1) {
#ifdef WIN32
        Sleep(L);
#else
        sleep((unsigned int)L / 1000);
#endif
      }
      else {
        T.tv_sec = L/1000;
        T.tv_usec = (L%1000)*1000;

        if(0 > select(M + 1, &R, &W, &E, &T)) {
          fprintf(stderr, "E: select(%i,,,,%li): %i: %s\n",
              M + 1, L, errno, strerror(errno));
          return EXIT_FAILURE;
        }
      }
    }

    while((msg = curl_multi_info_read(cm, &Q))) {
      if(msg->msg == CURLMSG_DONE) {
        char *url;
        CURL *e = msg->easy_handle;
        curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE, &url);
        fprintf(stderr, "R: %d - %s <%s>\n",
                msg->data.result, curl_easy_strerror(msg->data.result), url);
        curl_multi_remove_handle(cm, e);
        curl_easy_cleanup(e);
      }
      else {
        fprintf(stderr, "E: CURLMsg (%d)\n", msg->msg);
      }
      if(C < CNT) {
        init(cm, C++);
        U++; /* just to prevent it from remaining at 0 if there are more
                URLs to get */
      }
    }
  }

  curl_multi_cleanup(cm);
  curl_global_cleanup();

  return EXIT_SUCCESS;
}