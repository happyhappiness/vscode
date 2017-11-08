static CURLMcode perform(CURLM * multi)
{
  int handles, maxfd;
  CURLMcode code;
  fd_set fdread, fdwrite, fdexcep;
  struct timeval mp_start;
  char mp_timedout = FALSE;

  mp_timedout = FALSE;
  mp_start = tutil_tvnow();

  for (;;) {
    code = curl_multi_perform(multi, &handles);
    if (tutil_tvdiff(tutil_tvnow(), mp_start) > 
        MULTI_PERFORM_HANG_TIMEOUT) {
      mp_timedout = TRUE;
      break;
    }
    if (handles <= 0)
      return CURLM_OK;

    switch (code) {
      case CURLM_OK:
        break;
      case CURLM_CALL_MULTI_PERFORM:
        continue;
      default:
        return code;
    }

    FD_ZERO(&fdread);
    FD_ZERO(&fdwrite);
    FD_ZERO(&fdexcep);
    curl_multi_fdset(multi, &fdread, &fdwrite, &fdexcep, &maxfd);
    if (maxfd < 0)
      return (CURLMcode) ~CURLM_OK;
    if (select(maxfd + 1, &fdread, &fdwrite, &fdexcep, 0) == -1)
      return (CURLMcode) ~CURLM_OK;
  }

  /* We only reach this point if (mp_timedout) */
  if (mp_timedout) fprintf(stderr, "mp_timedout\n");
  fprintf(stderr, "ABORTING TEST, since it seems "
          "that it would have run forever.\n");
  return (CURLMcode) ~CURLM_OK;
}