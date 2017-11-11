int test(char *URL)
{
  int res = 0;
  CURL *curl = NULL;
  int i;
  char target_url[256];
  char dnsentry[256];
  struct curl_slist *slist = NULL, *slist2;
  char *port = libtest_arg3;
  char *address = libtest_arg2;

  (void)URL;

  /* Create fake DNS entries for serverX.example.com for all handles */
  for(i=0; i < NUM_URLS; i++) {
    snprintf(dnsentry, sizeof(dnsentry), "server%d.example.com:%s:%s", i + 1,
             port, address);
    printf("%s\n", dnsentry);
    slist2 = curl_slist_append(slist, dnsentry);
    if(!slist2) {
      fprintf(stderr, "curl_slist_append() failed\n");
      goto test_cleanup;
    }
    slist = slist2;
  }

  start_test_timing();

  global_init(CURL_GLOBAL_ALL);

  /* get an easy handle */
  easy_init(curl);

  /* go verbose */
  easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  /* include headers */
  easy_setopt(curl, CURLOPT_HEADER, 1L);

  easy_setopt(curl, CURLOPT_RESOLVE, slist);

  easy_setopt(curl, CURLOPT_MAXCONNECTS, 3L);

  /* get NUM_HANDLES easy handles */
  for(i=0; i < NUM_URLS; i++) {
    /* specify target */
    snprintf(target_url, sizeof(target_url),
             "http://server%d.example.com:%s/path/1510%04i",
             i + 1, port, i + 1);
    target_url[sizeof(target_url) - 1] = '\0';
    easy_setopt(curl, CURLOPT_URL, target_url);

    res = curl_easy_perform(curl);

    abort_on_test_timeout();
  }

test_cleanup:

  /* proper cleanup sequence - type PB */

  curl_easy_cleanup(curl);

  curl_slist_free_all(slist);

  curl_global_cleanup();

  return res;
}