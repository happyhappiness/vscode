int test(char *URL)
{
  CURL *handle = NULL;
  CURLM *mhandle = NULL;
  int res = 0;
  int still_running = 0;

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  easy_init(handle);

  easy_setopt(handle, CURLOPT_URL, URL);
  easy_setopt(handle, CURLOPT_VERBOSE, 1L);

  multi_init(mhandle);

  multi_add_handle(mhandle, handle);

  multi_perform(mhandle, &still_running);

  abort_on_test_timeout();

  while(still_running) {
    struct timeval timeout;
    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    int maxfd = -99;
    struct timeval before;
    struct timeval after;
    int e;

    timeout.tv_sec = 0;
    timeout.tv_usec = 100000L; /* 100 ms */

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    multi_fdset(mhandle, &fdread, &fdwrite, &fdexcep, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    select_test(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);

    abort_on_test_timeout();

    fprintf(stderr, "ping\n");
    before = tutil_tvnow();

    multi_perform(mhandle, &still_running);

    abort_on_test_timeout();

    after = tutil_tvnow();
    e = elapsed(&before, &after);
    fprintf(stderr, "pong = %d\n", e);

    if(e > MAX_BLOCKED_TIME_US) {
      res = 100;
      break;
    }
  }

test_cleanup:

  /* undocumented cleanup sequence - type UA */

  curl_multi_cleanup(mhandle);
  curl_easy_cleanup(handle);
  curl_global_cleanup();

  return res;
}