static CURLcode send_request(CURL *curl, const char *url, int seq,
                             long auth_scheme, const char *userpwd)
{
  CURLcode res;
  char* full_url = malloc(strlen(url) + 4 + 1);
  if (!full_url) {
    fprintf(stderr, "Not enough memory for full url\n");
    return CURLE_OUT_OF_MEMORY;
  }

  sprintf(full_url, "%s%04d", url, seq);
  fprintf(stderr, "Sending new request %d to %s with credential %s "
          "(auth %ld)\n", seq, full_url, userpwd, auth_scheme);
  test_setopt(curl, CURLOPT_URL, full_url);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);
  test_setopt(curl, CURLOPT_HEADER, 1L);
  test_setopt(curl, CURLOPT_HTTPGET, 1L);
  test_setopt(curl, CURLOPT_USERPWD, userpwd);
  test_setopt(curl, CURLOPT_HTTPAUTH, auth_scheme);

  res = curl_easy_perform(curl);

test_cleanup:
  free(full_url);
  return res;
}