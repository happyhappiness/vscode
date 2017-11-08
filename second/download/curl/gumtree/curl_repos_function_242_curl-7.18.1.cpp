int test(char *URL)
{
  CURLM *multi;
  CURL *easy;
  int res = 0;

  if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if ((multi = curl_multi_init()) == NULL) {
    fprintf(stderr, "curl_multi_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  if ((easy = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_multi_cleanup(multi);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  curl_multi_setopt(multi, CURLMOPT_PIPELINING, 1);

  curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, fwrite);
  curl_easy_setopt(easy, CURLOPT_FAILONERROR, 1);
  curl_easy_setopt(easy, CURLOPT_URL, URL);

  if (curl_multi_add_handle(multi, easy) != CURLM_OK) {
    printf("curl_multi_add_handle() failed\n");
    res = TEST_ERR_MAJOR_BAD;
  } else {
    if (perform(multi) != CURLM_OK)
      printf("retrieve 1 failed\n");

    curl_multi_remove_handle(multi, easy);
  }
  curl_easy_reset(easy);

  curl_easy_setopt(easy, CURLOPT_FAILONERROR, 1);
  curl_easy_setopt(easy, CURLOPT_URL, libtest_arg2);

  if (curl_multi_add_handle(multi, easy) != CURLM_OK) {
    printf("curl_multi_add_handle() 2 failed\n");
    res = TEST_ERR_MAJOR_BAD;
  } else {
    if (perform(multi) != CURLM_OK)
      printf("retrieve 2 failed\n");

    curl_multi_remove_handle(multi, easy);
  }
  curl_easy_cleanup(easy);
  curl_multi_cleanup(multi);
  curl_global_cleanup();

  printf("Finished!\n");

  return res;
}