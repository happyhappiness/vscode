int test(char *URL)
{
  CURL *curl, *dupe = NULL;
  long protocol;
  int res = CURLE_OK;

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  /* Test that protocol is properly initialized on curl_easy_init.
  */

  res = curl_easy_getinfo(curl, CURLINFO_PROTOCOL, &protocol);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(protocol != 0) {
    fprintf(stderr, "%s:%d protocol init failed; expected 0 but is %ld\n",
            __FILE__, __LINE__, protocol);
    res = CURLE_FAILED_INIT;
    goto test_cleanup;
  }

  easy_setopt(curl, CURLOPT_URL, URL);

  res = curl_easy_perform(curl);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_perform() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }

  /* Test that a protocol is properly set after receiving an HTTP resource.
  */

  res = curl_easy_getinfo(curl, CURLINFO_PROTOCOL, &protocol);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(protocol != CURLPROTO_HTTP) {
    fprintf(stderr, "%s:%d protocol of http resource is incorrect; "
            "expected %ld but is %ld\n",
            __FILE__, __LINE__, CURLPROTO_HTTP, protocol);
    res = CURLE_HTTP_RETURNED_ERROR;
    goto test_cleanup;
  }

  /* Test that a protocol is properly initialized on curl_easy_duphandle.
  */

  dupe = curl_easy_duphandle(curl);
  if(!dupe) {
    fprintf(stderr, "%s:%d curl_easy_duphandle() failed\n",
            __FILE__, __LINE__);
    res = CURLE_FAILED_INIT;
    goto test_cleanup;
  }

  res = curl_easy_getinfo(dupe, CURLINFO_PROTOCOL, &protocol);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(protocol != 0) {
    fprintf(stderr, "%s:%d protocol init failed; expected 0 but is %ld\n",
            __FILE__, __LINE__, protocol);
    res = CURLE_FAILED_INIT;
    goto test_cleanup;
  }


  /* Test that a protocol is properly initialized on curl_easy_reset.
  */

  curl_easy_reset(curl);

  res = curl_easy_getinfo(curl, CURLINFO_PROTOCOL, &protocol);
  if(res) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed with code %d (%s)\n",
            __FILE__, __LINE__, res, curl_easy_strerror(res));
    goto test_cleanup;
  }
  if(protocol != 0) {
    fprintf(stderr, "%s:%d protocol init failed; expected 0 but is %ld\n",
            __FILE__, __LINE__, protocol);
    res = CURLE_FAILED_INIT;
    goto test_cleanup;
  }

test_cleanup:
  curl_easy_cleanup(curl);
  curl_easy_cleanup(dupe);
  curl_global_cleanup();
  return res;
}