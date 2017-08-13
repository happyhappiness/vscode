 */
CURL *curl_easy_init(void)
{
  CURLcode result;
  struct SessionHandle *data;

  /* Make sure we inited the global SSL stuff */
  if(!initialized) {
    result = curl_global_init(CURL_GLOBAL_DEFAULT);
    if(result) {
      /* something in the global init failed, return nothing */
      DEBUGF(fprintf(stderr, "Error: curl_global_init failed\n"));
      return NULL;
    }
  }

  /* We use curl_open() with undefined URL so far */
  result = Curl_open(&data);
  if(result) {
    DEBUGF(fprintf(stderr, "Error: Curl_open failed\n"));
    return NULL;
  }
