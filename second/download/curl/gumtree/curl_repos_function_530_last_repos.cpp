int test(char *URL)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *slist = NULL;
  struct WriteThis pooh;
  pooh.counter = 0;

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

  slist = curl_slist_append(slist, "Transfer-Encoding: chunked");
  if(slist == NULL) {
    fprintf(stderr, "curl_slist_append() failed\n");
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  /* First set the URL that is about to receive our POST. */
  test_setopt(curl, CURLOPT_URL, URL);

  /* Now specify we want to POST data */
  test_setopt(curl, CURLOPT_POST, 1L);

#ifdef CURL_DOES_CONVERSIONS
  /* Convert the POST data to ASCII */
  test_setopt(curl, CURLOPT_TRANSFERTEXT, 1L);
#endif

  /* we want to use our own read function */
  test_setopt(curl, CURLOPT_READFUNCTION, read_callback);

  /* pointer to pass to our read function */
  test_setopt(curl, CURLOPT_READDATA, &pooh);

  /* get verbose debug output please */
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* include headers in the output */
  test_setopt(curl, CURLOPT_HEADER, 1L);

  /* enforce chunked transfer by setting the header */
  test_setopt(curl, CURLOPT_HTTPHEADER, slist);

  test_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_DIGEST);
  test_setopt(curl, CURLOPT_USERPWD, "foo:bar");

  /* we want to use our own progress function */
  test_setopt(curl, CURLOPT_NOPROGRESS, 0L);
  test_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);

  /* Perform the request, res will get the return code */
  res = curl_easy_perform(curl);

test_cleanup:

  /* clean up the headers list */
  if(slist)
    curl_slist_free_all(slist);

  /* always cleanup */
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return res;
}