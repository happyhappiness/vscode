int test(char *URL)
{
  long headerSize;
  CURLcode code;
  CURL *curl = NULL;
  int res = 0;

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_PROXY, libtest_arg2); /* set in first.c */

  easy_setopt(curl, CURLOPT_WRITEFUNCTION, *WriteOutput);
  easy_setopt(curl, CURLOPT_HEADERFUNCTION, *WriteHeader);

  easy_setopt(curl, CURLOPT_HEADER, 1L);
  easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1L);

  code = curl_easy_perform(curl);
  if(CURLE_OK != code) {
    fprintf(stderr, "%s:%d curl_easy_perform() failed, "
            "with code %d (%s)\n",
            __FILE__, __LINE__, (int)code, curl_easy_strerror(code));
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }

  code = curl_easy_getinfo(curl, CURLINFO_HEADER_SIZE, &headerSize);
  if(CURLE_OK != code) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed, "
            "with code %d (%s)\n",
            __FILE__, __LINE__, (int)code, curl_easy_strerror(code));
    res = TEST_ERR_MAJOR_BAD;
    goto test_cleanup;
  }

  printf("header length is ........: %lu\n", headerSize);
  printf("header length should be..: %lu\n", realHeaderSize);

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}