int test(char *URL)
{
  CURLM* multi = NULL;
  int res = 0;
  char *address = libtest_arg2;
  char *port = libtest_arg3;
  char *path = URL;
  char dns_entry[256];
  int i;
  int count = 2;

  snprintf(dns_entry, sizeof(dns_entry), "testserver.example.com:%s:%s",
           port, address);

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);
  multi_init(multi);

  for(i = 1; i <= count; i++) {
    char target_url[256];
    snprintf(target_url, sizeof(target_url),
             "http://testserver.example.com:%s/%s%04d", port, path, i);

    /* second request must succeed like the first one */
    if((res = do_one_request(multi, target_url, dns_entry)))
      goto test_cleanup;

    if(i < count)
      sleep(DNS_TIMEOUT + 1);
  }

test_cleanup:

  curl_multi_cleanup(multi);

  return (int) res;
}