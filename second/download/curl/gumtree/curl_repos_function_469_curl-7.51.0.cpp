int test(char *URL)
{
  int res = 0;
  CURL *curl = NULL;
  int running;
  CURLM *m = NULL;
  int current=0;

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

  multi_init(m);

  multi_add_handle(m, curl);

  fprintf(stderr, "Start at URL 0\n");

  for(;;) {
    struct timeval interval;
    fd_set rd, wr, exc;
    int maxfd = -99;

    interval.tv_sec = 1;
    interval.tv_usec = 0;

    multi_perform(m, &running);

    abort_on_test_timeout();

    if(!running) {
      if(!current++) {
        fprintf(stderr, "Advancing to URL 1\n");
        /* remove the handle we use */
        curl_multi_remove_handle(m, curl);

        /* make us re-use the same handle all the time, and try resetting
           the handle first too */
        curl_easy_reset(curl);
        easy_setopt(curl, CURLOPT_URL, libtest_arg2);
        easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

        /* re-add it */
        multi_add_handle(m, curl);
      }
      else
        break; /* done */
    }

    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&exc);

    multi_fdset(m, &rd, &wr, &exc, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    select_test(maxfd+1, &rd, &wr, &exc, &interval);

    abort_on_test_timeout();
  }

test_cleanup:

  /* undocumented cleanup sequence - type UB */

  curl_easy_cleanup(curl);
  curl_multi_cleanup(m);
  curl_global_cleanup();

  return res;
}