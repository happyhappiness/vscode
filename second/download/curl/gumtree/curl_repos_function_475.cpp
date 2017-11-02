int test(char *URL)
{
  CURL *curl;
  CURLcode res = CURLE_FAILED_INIT;
  int i;
  struct curl_slist *headerlist=NULL, *hl;

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  for (i = 0; i < NUM_HEADERS; i++) {
    int len = sprintf(buf, "Header%d: ", i);
    memset(&buf[len], 'A', SIZE_HEADERS);
    buf[len + SIZE_HEADERS]=0; /* zero terminate */
    hl = curl_slist_append(headerlist,  buf);
    if (!hl)
      goto test_cleanup;
    headerlist = hl;
  }

  hl = curl_slist_append(headerlist, "Expect: ");
  if (!hl)
    goto test_cleanup;
  headerlist = hl;

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
  test_setopt(curl, CURLOPT_POST, 1L);
#ifdef CURL_DOES_CONVERSIONS
  /* Convert the POST data to ASCII */
  test_setopt(curl, CURLOPT_TRANSFERTEXT, 1L);
#endif
  test_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)POSTLEN);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);
  test_setopt(curl, CURLOPT_HEADER, 1L);
  test_setopt(curl, CURLOPT_READFUNCTION, myreadfunc);

  res = curl_easy_perform(curl);

test_cleanup:

  curl_easy_cleanup(curl);

  curl_slist_free_all(headerlist);

  curl_global_cleanup();

  return (int)res;
}