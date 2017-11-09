static int xferinfo(void *p,
                    curl_off_t dltotal, curl_off_t dlnow,
                    curl_off_t ultotal, curl_off_t ulnow)
{
  struct myprogress *myp = (struct myprogress *)p;
  CURL *curl = myp->curl;
  double curtime = 0;

  curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &curtime);

  /* under certain circumstances it may be desirable for certain functionality
     to only run every N seconds, in order to do this the transaction time can
     be used */
  if((curtime - myp->lastruntime) >= MINIMAL_PROGRESS_FUNCTIONALITY_INTERVAL) {
    myp->lastruntime = curtime;
    fprintf(stderr, "TOTAL TIME: %f \r\n", curtime);
  }

  fprintf(stderr, "UP: %" CURL_FORMAT_CURL_OFF_T " of %" CURL_FORMAT_CURL_OFF_T
          "  DOWN: %" CURL_FORMAT_CURL_OFF_T " of %" CURL_FORMAT_CURL_OFF_T
          "\r\n",
          ulnow, ultotal, dlnow, dltotal);

  if(dlnow > STOP_DOWNLOAD_AFTER_THIS_MANY_BYTES)
    return 1;
  return 0;
}