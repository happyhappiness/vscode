int test(char *URL)
{
  CURLcode res;
  CURL *curl;

  if(!strcmp(URL, "check")) {
    /* used by the test script to ask if we can run this test or not */
    if(rlimit(FALSE)) {
      fprintf(stdout, "rlimit problem: %s\n", msgbuff);
      return 1;
    }
    return 0; /* sure, run this! */
  }

  if(rlimit(TRUE)) {
    /* failure */
    return TEST_ERR_MAJOR_BAD;
  }

  /* run the test with the bunch of open file descriptors
     and close them all once the test is over */

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    close_file_descriptors();
    return TEST_ERR_MAJOR_BAD;
  }

  curl = curl_easy_init();
  if(!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    close_file_descriptors();
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_HEADER, 1L);

  res = curl_easy_perform(curl);

test_cleanup:

  close_file_descriptors();
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}