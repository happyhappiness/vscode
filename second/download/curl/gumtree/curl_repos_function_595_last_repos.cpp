int test(char *URL)
{
  CURL *c = NULL;
  int res = 0;
  CURLM *m = NULL;
  fd_set rd, wr, exc;
  int running;

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  easy_init(c);

  /* The point here is that there must not be anything running on the given
     proxy port */
  if(libtest_arg2)
    easy_setopt(c, CURLOPT_PROXY, libtest_arg2);
  easy_setopt(c, CURLOPT_URL, URL);
  easy_setopt(c, CURLOPT_VERBOSE, 1L);

  multi_init(m);

  multi_add_handle(m, c);

  for(;;) {
    struct timeval interval;
    int maxfd = -99;

    interval.tv_sec = 1;
    interval.tv_usec = 0;

    fprintf(stderr, "curl_multi_perform()\n");

    multi_perform(m, &running);

    abort_on_test_timeout();

    if(!running) {
      /* This is where this code is expected to reach */
      int numleft;
      CURLMsg *msg = curl_multi_info_read(m, &numleft);
      fprintf(stderr, "Expected: not running\n");
      if(msg && !numleft)
        res = TEST_ERR_SUCCESS; /* this is where we should be */
      else
        res = TEST_ERR_FAILURE; /* not correct */
      break; /* done */
    }
    fprintf(stderr, "running == %d\n", running);

    FD_ZERO(&rd);
    FD_ZERO(&wr);
    FD_ZERO(&exc);

    fprintf(stderr, "curl_multi_fdset()\n");

    multi_fdset(m, &rd, &wr, &exc, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    select_test(maxfd + 1, &rd, &wr, &exc, &interval);

    abort_on_test_timeout();
  }

test_cleanup:

  /* proper cleanup sequence - type PA */

  curl_multi_remove_handle(m, c);
  curl_multi_cleanup(m);
  curl_easy_cleanup(c);
  curl_global_cleanup();

  return res;
}