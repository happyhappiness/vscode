int test(char *url)
{
  CURLM *multi = NULL;
  int running;
  int i;
  int num_handles = 0;
  enum HandleState state = ReadyForNewHandle;
  size_t urllen = strlen(url) + 4 + 1;
  char *full_url = malloc(urllen);

  start_test_timing();

  if(!full_url) {
    fprintf(stderr, "Not enough memory for full url\n");
    return TEST_ERR_MAJOR_BAD;
  }

  for(i = 0; i < MAX_EASY_HANDLES; ++i) {
    easy[i] = NULL;
    sockets[i] = CURL_SOCKET_BAD;
  }

  res_global_init(CURL_GLOBAL_ALL);
  if(res) {
    free(full_url);
    return res;
  }

  multi_init(multi);

#ifdef USE_PIPELINING
  multi_setopt(multi, CURLMOPT_PIPELINING, 1L);
  multi_setopt(multi, CURLMOPT_MAX_HOST_CONNECTIONS, 5L);
  multi_setopt(multi, CURLMOPT_MAX_TOTAL_CONNECTIONS, 10L);
#endif

  for(;;) {
    struct timeval interval;
    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    long timeout = -99;
    int maxfd = -99;
    bool found_new_socket = FALSE;

    /* Start a new handle if we aren't at the max */
    if(state == ReadyForNewHandle) {
      easy_init(easy[num_handles]);

      if(num_handles % 3 == 2) {
        snprintf(full_url, urllen, "%s0200", url);
        easy_setopt(easy[num_handles], CURLOPT_HTTPAUTH, CURLAUTH_NTLM);
      }
      else {
        snprintf(full_url, urllen, "%s0100", url);
        easy_setopt(easy[num_handles], CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
      }
      easy_setopt(easy[num_handles], CURLOPT_FRESH_CONNECT, 1L);
      easy_setopt(easy[num_handles], CURLOPT_URL, full_url);
      easy_setopt(easy[num_handles], CURLOPT_VERBOSE, 1L);
      easy_setopt(easy[num_handles], CURLOPT_HTTPGET, 1L);
      easy_setopt(easy[num_handles], CURLOPT_USERPWD, "testuser:testpass");
      easy_setopt(easy[num_handles], CURLOPT_WRITEFUNCTION, callback);
      easy_setopt(easy[num_handles], CURLOPT_WRITEDATA, easy + num_handles);
      easy_setopt(easy[num_handles], CURLOPT_HEADER, 1L);

      multi_add_handle(multi, easy[num_handles]);
      num_handles += 1;
      state = NeedSocketForNewHandle;
    }

    multi_perform(multi, &running);

    abort_on_test_timeout();

    if(!running && state == NoMoreHandles)
      break; /* done */

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    multi_fdset(multi, &fdread, &fdwrite, &fdexcep, &maxfd);

    /* At this point, maxfd is guaranteed to be greater or equal than -1. */

    if(state == NeedSocketForNewHandle) {
      if(maxfd != -1 && !found_new_socket) {
        fprintf(stderr, "Warning: socket did not open immediately for new "
                "handle (trying again)\n");
        continue;
      }
      state = num_handles < MAX_EASY_HANDLES ? ReadyForNewHandle
                                             : NoMoreHandles;
    }

    multi_timeout(multi, &timeout);

    /* At this point, timeout is guaranteed to be greater or equal than -1. */

    fprintf(stderr, "%s:%d num_handles %d timeout %ld\n",
            __FILE__, __LINE__, num_handles, timeout);

    if(timeout != -1L) {
      int itimeout = (timeout > (long)INT_MAX) ? INT_MAX : (int)timeout;
      interval.tv_sec = itimeout/1000;
      interval.tv_usec = (itimeout%1000)*1000;
    }
    else {
      interval.tv_sec = TEST_HANG_TIMEOUT/1000 + 1;
      interval.tv_usec = 0;

      /* if there's no timeout and we get here on the last handle, we may
         already have read the last part of the stream so waiting makes no
         sense */
      if(!running && num_handles == MAX_EASY_HANDLES) {
        break;
      }
    }

    select_test(maxfd + 1, &fdread, &fdwrite, &fdexcep, &interval);

    abort_on_test_timeout();
  }

test_cleanup:

  /* proper cleanup sequence - type PB */

  for(i = 0; i < MAX_EASY_HANDLES; i++) {
    printf("Data connection %d: %d\n", i, counter[i]);
    curl_multi_remove_handle(multi, easy[i]);
    curl_easy_cleanup(easy[i]);
  }

  curl_multi_cleanup(multi);
  curl_global_cleanup();

  free(full_url);

  return res;
}