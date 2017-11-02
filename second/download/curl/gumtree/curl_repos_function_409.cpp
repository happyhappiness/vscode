int test(char *URL)
{
  CURL *http_handle = NULL;
  CURLM *multi_handle = NULL;
  int res = 0;

  int still_running; /* keep number of running handles */

  start_test_timing();

  /*
  ** curl_global_init called indirectly from curl_easy_init.
  */

  easy_init(http_handle);

  /* set options */
  easy_setopt(http_handle, CURLOPT_URL, URL);
  easy_setopt(http_handle, CURLOPT_HEADER, 1L);
  easy_setopt(http_handle, CURLOPT_SSL_VERIFYPEER, 0L);
  easy_setopt(http_handle, CURLOPT_SSL_VERIFYHOST, 0L);

  /* init a multi stack */
  multi_init(multi_handle);

  /* add the individual transfers */
  multi_add_handle(multi_handle, http_handle);

  /* we start some action by calling perform right away */
  multi_perform(multi_handle, &still_running);

  abort_on_test_timeout();

  while(still_running) {
    struct timeval timeout;

    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    int maxfd = -99;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    /* set a suitable timeout to play around with */
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    /* get file descriptors from the transfers */
    multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    select_test(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);

    abort_on_test_timeout();

    /* timeout or readable/writable sockets */
    multi_perform(multi_handle, &still_running);

    abort_on_test_timeout();
  }

test_cleanup:

  /* undocumented cleanup sequence - type UA */

  curl_multi_cleanup(multi_handle);
  curl_easy_cleanup(http_handle);
  curl_global_cleanup();

  return res;
}