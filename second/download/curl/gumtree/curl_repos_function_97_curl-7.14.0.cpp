int test(char *URL)
{
  CURLcode res;
  CURL *curl;

  if(!strcmp(URL, "check")) {
    /* used by the test script to ask if we can run this test or not */
    if(rlimit()) {
      printf("rlimit problems\n");
      return 1;
    }
    return 0; /* sure, run this! */
  }

  if(rlimit())
    /* failure */
    return 100;

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, URL);
  curl_easy_setopt(curl, CURLOPT_HEADER, TRUE);
  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  /* we never close the file descriptors */

  return (int)res;
}