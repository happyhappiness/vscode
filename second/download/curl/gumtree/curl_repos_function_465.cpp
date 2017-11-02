int test(char *URL)
{
  CURLcode res;
  CURL *curl;
  struct curl_slist *rcpt_list = NULL;
  struct upload_status upload_ctx = {0};

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  rcpt_list = curl_slist_append(rcpt_list, TO);
  /* more addresses can be added here
     rcpt_list = curl_slist_append(rcpt_list, "<others@example.com>");
  */

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_UPLOAD, 1L);
  test_setopt(curl, CURLOPT_READFUNCTION, read_callback);
  test_setopt(curl, CURLOPT_READDATA, &upload_ctx);
  test_setopt(curl, CURLOPT_MAIL_FROM, FROM);
  test_setopt(curl, CURLOPT_MAIL_RCPT, rcpt_list);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  res = curl_easy_perform(curl);

test_cleanup:

  curl_slist_free_all(rcpt_list);
  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}