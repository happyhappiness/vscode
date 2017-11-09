int test(char *URL)
{
  int res = 0;
  CURLM *m = NULL;

  (void)URL;

  global_init(CURL_GLOBAL_ALL);

  multi_init(m);

test_cleanup:

  /* proper cleanup sequence - type PB */

  curl_multi_cleanup(m);
  curl_global_cleanup();

  printf("We are done\n");

  return res;
}