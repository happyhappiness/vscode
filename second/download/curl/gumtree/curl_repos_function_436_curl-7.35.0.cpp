int test(char *URL)
{
  CURLM *cm = NULL;
  struct curl_slist *headers = NULL;
  char buffer[246]; /* naively fixed-size */
  int res = 0;
  int i;

  for(i=0; i < NUM_HANDLES; i++)
    eh[i] = NULL;

  start_test_timing();

  if(test_argc < 4)
    return 99;

  sprintf(buffer, "Host: %s", HOST);

  /* now add a custom Host: header */
  headers = curl_slist_append(headers, buffer);
  if(!headers) {
    fprintf(stderr, "curl_slist_append() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  res_global_init(CURL_GLOBAL_ALL);
  if(res) {
    curl_slist_free_all(headers);
    return res;
  }

  res_multi_init(cm);
  if(res) {
    curl_global_cleanup();
    curl_slist_free_all(headers);
    return res;
  }

  res = loop(0, cm, URL, PROXYUSERPWD, headers);
  if(res)
    goto test_cleanup;

  fprintf(stderr, "lib540: now we do the request again\n");

  res = loop(1, cm, URL, PROXYUSERPWD, headers);

test_cleanup:

  /* proper cleanup sequence - type PB */

  for(i=0; i < NUM_HANDLES; i++) {
    curl_multi_remove_handle(cm, eh[i]);
    curl_easy_cleanup(eh[i]);
  }

  curl_multi_cleanup(cm);
  curl_global_cleanup();

  curl_slist_free_all(headers);

  return res;
}