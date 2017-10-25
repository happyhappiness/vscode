CURLcode curl_easy_perform(CURL *easy)
{
  CURLM *multi;
  CURLMcode mcode;
  CURLcode code = CURLE_OK;
  int still_running;
  struct timeval timeout;
  int rc;
  CURLMsg *msg;
  fd_set fdread;
  fd_set fdwrite;
  fd_set fdexcep;
  int maxfd;

  if(!easy)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  multi = curl_multi_init();
  if(!multi)
    return CURLE_OUT_OF_MEMORY;

  mcode = curl_multi_add_handle(multi, easy);
  if(mcode) {
    curl_multi_cleanup(multi);
    return CURLE_FAILED_INIT;
  }

  /* we start some action by calling perform right away */

  do {
    while(CURLM_CALL_MULTI_PERFORM ==
          curl_multi_perform(multi, &still_running));

    if(!still_running)
      break;

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);

    /* timeout once per second */
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    /* get file descriptors from the transfers */
    curl_multi_fdset(multi, &fdread, &fdwrite, &fdexcep, &maxfd);

    rc = select(maxfd+1, &fdread, &fdwrite, &fdexcep, &timeout);

    if(rc == -1)
      /* select error */
      break;

    /* timeout or data to send/receive => loop! */
  } while(still_running);

  msg = curl_multi_info_read(multi, &rc);
  if(msg)
    code = msg->data.result;

  mcode = curl_multi_remove_handle(multi, easy);
  /* what to do if it fails? */

  mcode = curl_multi_cleanup(multi);
  /* what to do if it fails? */

  return code;
}