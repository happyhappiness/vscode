int test(char *URL)
{
  CURL *easy = NULL;
  CURLM *multi = NULL;
  int res = 0;
  int running;
  int msgs_left;
  CURLMsg *msg;
  FILE *upload = NULL;
  int error;

  start_test_timing();

  upload = fopen(libtest_arg3, "rb");
  if(!upload) {
    error = ERRNO;
    fprintf(stderr, "fopen() failed with error: %d (%s)\n",
            error, strerror(error));
    fprintf(stderr, "Error opening file: (%s)\n", libtest_arg3);
    return TEST_ERR_FOPEN;
  }

  res_global_init(CURL_GLOBAL_ALL);
  if(res) {
    fclose(upload);
    return res;
  }

  easy_init(easy);

  /* go verbose */
  easy_setopt(easy, CURLOPT_VERBOSE, 1L);

  /* specify target */
  easy_setopt(easy, CURLOPT_URL, URL);

  /* enable uploading */
  easy_setopt(easy, CURLOPT_UPLOAD, 1L);

  /* data pointer for the file read function */
  easy_setopt(easy, CURLOPT_READDATA, upload);

  /* use active mode FTP */
  easy_setopt(easy, CURLOPT_FTPPORT, "-");

  /* server connection timeout */
  easy_setopt(easy, CURLOPT_ACCEPTTIMEOUT_MS,
              strtol(libtest_arg2, NULL, 10)*1000);

  multi_init(multi);

  multi_add_handle(multi, easy);

  for(;;) {
    struct timeval interval;
    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    long timeout = -99;
    int maxfd = -99;

    multi_perform(multi, &running);

    abort_on_test_timeout();

    if(!running)
      break; /* done */

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    multi_fdset(multi, &fdread, &fdwrite, &fdexcep, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    multi_timeout(multi, &timeout);

    /* At this point, timeout is guaranteed to be greater or equal than -1. */

    if(timeout != -1L) {
      int itimeout = (timeout > (long)INT_MAX) ? INT_MAX : (int)timeout;
      interval.tv_sec = itimeout/1000;
      interval.tv_usec = (itimeout%1000)*1000;
    }
    else {
      interval.tv_sec = 0;
      interval.tv_usec = 100000L; /* 100 ms */
    }

    select_test(maxfd+1, &fdread, &fdwrite, &fdexcep, &interval);

    abort_on_test_timeout();
  }

  msg = curl_multi_info_read(multi, &msgs_left);
  if(msg)
    res = msg->data.result;

test_cleanup:

  /* undocumented cleanup sequence - type UA */

  curl_multi_cleanup(multi);
  curl_easy_cleanup(easy);
  curl_global_cleanup();

  /* close the local file */
  fclose(upload);

  return res;
}