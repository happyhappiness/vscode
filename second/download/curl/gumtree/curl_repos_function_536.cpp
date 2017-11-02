int test(char *URL)
{
  int res = 0;
  CURL *curl = NULL;
  int counter=0;
  CURLM *m = NULL;
  int running=1;

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  easy_setopt(curl, CURLOPT_HEADER, 1L);

  /* read the POST data from a callback */
  easy_setopt(curl, CURLOPT_IOCTLFUNCTION, ioctlcallback);
  easy_setopt(curl, CURLOPT_IOCTLDATA, &counter);
  easy_setopt(curl, CURLOPT_READFUNCTION, readcallback);
  easy_setopt(curl, CURLOPT_READDATA, &counter);
  /* We CANNOT do the POST fine without setting the size (or choose chunked)! */
  easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(UPLOADTHIS));

  easy_setopt(curl, CURLOPT_POST, 1L);
#ifdef CURL_DOES_CONVERSIONS
  /* Convert the POST data to ASCII. */
  easy_setopt(curl, CURLOPT_TRANSFERTEXT, 1L);
#endif
  easy_setopt(curl, CURLOPT_PROXY, libtest_arg2);
  easy_setopt(curl, CURLOPT_PROXYUSERPWD, libtest_arg3);
  easy_setopt(curl, CURLOPT_PROXYAUTH,
                   (long) (CURLAUTH_NTLM | CURLAUTH_DIGEST | CURLAUTH_BASIC) );

  multi_init(m);

  multi_add_handle(m, curl);

  while (running) {
    struct timeval timeout;
    fd_set fdread, fdwrite, fdexcep;
    int maxfd = -99;

    timeout.tv_sec = 0;
    timeout.tv_usec = 100000L; /* 100 ms */

    multi_perform(m, &running);

    abort_on_test_timeout();

#ifdef TPF
    sleep(1); /* avoid ctl-10 dump */
#endif

    if(!running)
      break; /* done */

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    multi_fdset(m, &fdread, &fdwrite, &fdexcep, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    select_test(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);

    abort_on_test_timeout();
  }

test_cleanup:

  /* proper cleanup sequence - type PA */

  curl_multi_remove_handle(m, curl);
  curl_multi_cleanup(m);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}