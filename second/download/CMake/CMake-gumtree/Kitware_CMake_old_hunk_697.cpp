 */

CURL *curl_easy_init(void)

{

  CURLcode res;

  struct SessionHandle *data;



  /* Make sure we inited the global SSL stuff */

  if(!initialized) {

    res = curl_global_init(CURL_GLOBAL_DEFAULT);

    if(res) {

      /* something in the global init failed, return nothing */

      DEBUGF(fprintf(stderr, "Error: curl_global_init failed\n"));

      return NULL;

    }

  }



  /* We use curl_open() with undefined URL so far */

  res = Curl_open(&data);

  if(res != CURLE_OK) {

    DEBUGF(fprintf(stderr, "Error: Curl_open failed\n"));

    return NULL;

  }

