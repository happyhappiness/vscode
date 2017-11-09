int test(char *URL)
{
  CURL *curl;
  CURLcode res = CURLE_OK;

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

  /* First set the URL that is about to receive our POST. */
  test_setopt(curl, CURLOPT_URL, URL);

#ifdef LIB545
  test_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) sizeof teststring);
#endif

  test_setopt(curl, CURLOPT_COPYPOSTFIELDS, teststring);

  test_setopt(curl, CURLOPT_VERBOSE, 1L); /* show verbose for debug */
  test_setopt(curl, CURLOPT_HEADER, 1L); /* include header */

  /* Update the original data to detect non-copy. */
  strcpy(teststring, "FAIL");

#ifdef LIB545
  {
    CURL *handle2;
    handle2 = curl_easy_duphandle(curl);
    curl_easy_cleanup(curl);

    curl = handle2;
  }
#endif

  /* Now, this is a POST request with binary 0 embedded in POST data. */
  res = curl_easy_perform(curl);

test_cleanup:

  /* always cleanup */
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}