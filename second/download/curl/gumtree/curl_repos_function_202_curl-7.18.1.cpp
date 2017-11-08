int test(char *URL)
{
  CURLM *cm;
  struct curl_slist *headers = NULL;
  char buffer[246]; /* naively fixed-size */

  if(test_argc < 4)
    return 99;

  sprintf(buffer, "Host: %s", HOST);

  /* now add a custom Host: header */
  headers = curl_slist_append(headers, buffer);

  curl_global_init(CURL_GLOBAL_ALL);

  cm = curl_multi_init();
  loop(cm, URL, PROXYUSERPWD, headers);

  fprintf(stderr, "lib540: now we do the request again\n");
  loop(cm, URL, PROXYUSERPWD, headers);

  curl_multi_cleanup(cm);

  curl_global_cleanup();

  curl_slist_free_all(headers);

  return EXIT_SUCCESS;
}