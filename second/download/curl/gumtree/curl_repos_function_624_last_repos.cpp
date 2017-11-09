int test(char *URL)
{
  CURL *curl;
  CURLcode result = CURLE_OK;
  int res = 0;
  struct WriteThis pooh = { data, sizeof(data)-1 };

  global_init(CURL_GLOBAL_ALL);

  easy_init(curl);

  easy_setopt(curl, CURLOPT_URL, URL);
  easy_setopt(curl, CURLOPT_POST, 1L);
  /* Purposely omit to set CURLOPT_POSTFIELDSIZE */
  easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
  easy_setopt(curl, CURLOPT_READDATA, &pooh);

  result = curl_easy_perform(curl);

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)result;
}