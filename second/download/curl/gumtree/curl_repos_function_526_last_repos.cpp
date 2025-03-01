int test(char *URL)
{
  CURLcode res;
  CURL *curl;
  struct curl_slist *custom_headers = NULL;

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  /* Dump data to stdout for protocol verification */
  test_setopt(curl, CURLOPT_HEADERDATA, stdout);
  test_setopt(curl, CURLOPT_WRITEDATA, stdout);

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_RTSP_STREAM_URI, URL);
  test_setopt(curl, CURLOPT_RTSP_REQUEST, CURL_RTSPREQ_OPTIONS);
  test_setopt(curl, CURLOPT_USERAGENT, "test567");

  custom_headers = curl_slist_append(custom_headers, "Test-Number: 567");
  test_setopt(curl, CURLOPT_RTSPHEADER, custom_headers);

  res = curl_easy_perform(curl);

test_cleanup:

  if(custom_headers)
    curl_slist_free_all(custom_headers);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}