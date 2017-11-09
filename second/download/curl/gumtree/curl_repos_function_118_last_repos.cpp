int main(int argc, char **argv)
{
  CURL *easy[NUM_HANDLES];
  CURLM *multi_handle;
  int i;
  int still_running; /* keep number of running handles */

  if(argc > 1)
    /* if given a number, do that many transfers */
    num_transfers = atoi(argv[1]);

  if(!num_transfers || (num_transfers > NUM_HANDLES))
    num_transfers = 3; /* a suitable low default */

  /* init a multi stack */
  multi_handle = curl_multi_init();

  for(i = 0; i<num_transfers; i++) {
    easy[i] = curl_easy_init();
    /* set options */
    setup(easy[i], i);

    /* add the individual transfer */
    curl_multi_add_handle(multi_handle, easy[i]);
  }

  curl_multi_setopt(multi_handle, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);

  /* we start some action by calling perform right away */
  curl_multi_perform(multi_handle, &still_running);

  do {
    struct timeval timeout;
    int rc; /* select() return code */
    CURLMcode mc; /* curl_multi_fdset() return code */

    fd_set fdread;
    fd_set fdwrite;
    fd_set fdexcep;
    int maxfd = -1;

    long curl_timeo = -1;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    /* set a suitable timeout to play around with */
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    curl_multi_timeout(multi_handle, &curl_timeo);
    if(curl_timeo >= 0) {
      timeout.tv_sec = curl_timeo / 1000;
      if(timeout.tv_sec > 1)
        timeout.tv_sec = 1;
      else
        timeout.tv_usec = (curl_timeo % 1000) * 1000;
    }

    /* get file descriptors from the transfers */
    mc = curl_multi_fdset(multi_handle, &fdread, &fdwrite, &fdexcep, &maxfd);

    if(mc != CURLM_OK) {
      fprintf(stderr, "curl_multi_fdset() failed, code %d.\n", mc);
      break;
    }

    /* On success the value of maxfd is guaranteed to be >= -1. We call
       select(maxfd + 1, ...); specially in case of (maxfd == -1) there are
       no fds ready yet so we call select(0, ...) --or Sleep() on Windows--
       to sleep 100ms, which is the minimum suggested value in the
       curl_multi_fdset() doc. */

    if(maxfd == -1) {
#ifdef _WIN32
      Sleep(100);
      rc = 0;
#else
      /* Portable sleep for platforms other than Windows. */
      struct timeval wait = { 0, 100 * 1000 }; /* 100ms */
      rc = select(0, NULL, NULL, NULL, &wait);
#endif
    }
    else {
      /* Note that on some platforms 'timeout' may be modified by select().
         If you need access to the original value save a copy beforehand. */
      rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
    }

    switch(rc) {
    case -1:
      /* select error */
      break;
    case 0:
    default:
      /* timeout or readable/writable sockets */
      curl_multi_perform(multi_handle, &still_running);
      break;
    }
  } while(still_running);

  curl_multi_cleanup(multi_handle);

  for(i = 0; i<num_transfers; i++)
    curl_easy_cleanup(easy[i]);

  return 0;
}