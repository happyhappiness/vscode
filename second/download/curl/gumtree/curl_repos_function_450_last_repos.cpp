static int perform_and_check_connections(CURL *curl, const char *description,
                                         long expected_connections)
{
  CURLcode res;
  long connections = 0;

  res = curl_easy_perform(curl);
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  res = curl_easy_getinfo(curl, CURLINFO_NUM_CONNECTS, &connections);
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_getinfo() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  fprintf(stderr, "%s: expected: %ld connections; actual: %ld connections\n",
          description, expected_connections, connections);

  if(connections != expected_connections) {
    return TEST_ERR_FAILURE;
  }

  return TEST_ERR_SUCCESS;
}