int test(char *URL)
{
  CURLM *multi = NULL;
  CURL *easy = NULL;
  int res = 0;

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  multi_init(multi);

  easy_init(easy);

  multi_setopt(multi, CURLMOPT_PIPELINING, 1L);

  easy_setopt(easy, CURLOPT_WRITEFUNCTION, fwrite);
  easy_setopt(easy, CURLOPT_FAILONERROR, 1L);
  easy_setopt(easy, CURLOPT_URL, URL);

  res_multi_add_handle(multi, easy);
  if(res) {
    printf("curl_multi_add_handle() 1 failed\n");
    goto test_cleanup;
  }

  res = perform(multi);
  if(res) {
    printf("retrieve 1 failed\n");
    goto test_cleanup;
  }

  curl_multi_remove_handle(multi, easy);

  curl_easy_reset(easy);

  easy_setopt(easy, CURLOPT_FAILONERROR, 1L);
  easy_setopt(easy, CURLOPT_URL, libtest_arg2);

  res_multi_add_handle(multi, easy);
  if(res) {
    printf("curl_multi_add_handle() 2 failed\n");
    goto test_cleanup;
  }

  res = perform(multi);
  if(res) {
    printf("retrieve 2 failed\n");
    goto test_cleanup;
  }

  curl_multi_remove_handle(multi, easy);

test_cleanup:

  /* undocumented cleanup sequence - type UB */

  curl_easy_cleanup(easy);
  curl_multi_cleanup(multi);
  curl_global_cleanup();

  printf("Finished!\n");

  return res;
}