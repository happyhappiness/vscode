static int fill_buffer(URL_FILE *file, size_t want)
{
  fd_set fdread;
  fd_set fdwrite;
  fd_set fdexcep;
  struct timeval timeout;
  int rc;
  CURLMcode mc; /* curl_multi_fdset() return code */

  /* only attempt to fill buffer if transactions still running and buffer
   * doesn't exceed required size already
   */
  if((!file->still_running) || (file->buffer_pos > want))
    return 0;

  /* attempt to fill buffer */
  do {
    int maxfd = -1;
    long curl_timeo = -1;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    /* set a suitable timeout to fail on */
    timeout.tv_sec = 60; /* 1 minute */
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
      curl_multi_perform(multi_handle, &file->still_running);
      break;
    }
  } while(file->still_running && (file->buffer_pos < want));
  return 1;
}