int test(char *URL)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

  if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  /* get a curl handle */
  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  /* enable verbose */
  curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE) ;

  /* enable NOBODY */
  curl_easy_setopt(curl, CURLOPT_NOBODY, TRUE) ;

  /* disable HEADER */
  curl_easy_setopt(curl, CURLOPT_HEADER, FALSE) ;

  /* specify target */
  curl_easy_setopt(curl,CURLOPT_URL, URL);

  /* Now run off and do what you've been told! */
  res = curl_easy_perform(curl);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}