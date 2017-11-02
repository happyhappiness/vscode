int test(char *url)
{
  CURLcode res;
  CURL *curl = NULL;

  long main_auth_scheme = parse_auth_name(libtest_arg2);
  long fallback_auth_scheme = parse_auth_name(libtest_arg3);

  if (main_auth_scheme == CURLAUTH_NONE ||
      fallback_auth_scheme == CURLAUTH_NONE) {
    fprintf(stderr, "auth schemes not found on commandline\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  /* Send wrong password, then right password */

  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  res = send_wrong_password(curl, url, 100, main_auth_scheme);
  if (res != CURLE_OK)
      goto test_cleanup;
  curl_easy_reset(curl);

  res = send_right_password(curl, url, 200, fallback_auth_scheme);
  if (res != CURLE_OK)
      goto test_cleanup;
  curl_easy_reset(curl);

  curl_easy_cleanup(curl);

  /* Send wrong password twice, then right password */

  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  res = send_wrong_password(curl, url, 300, main_auth_scheme);
  if (res != CURLE_OK)
      goto test_cleanup;
  curl_easy_reset(curl);

  res = send_wrong_password(curl, url, 400, fallback_auth_scheme);
  if (res != CURLE_OK)
      goto test_cleanup;
  curl_easy_reset(curl);

  res = send_right_password(curl, url, 500, fallback_auth_scheme);
  if (res != CURLE_OK)
      goto test_cleanup;
  curl_easy_reset(curl);

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}