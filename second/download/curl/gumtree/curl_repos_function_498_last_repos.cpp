int test(char *URL)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
  struct data config;
  size_t i;
  static const char fill[] = "test data";

  config.trace_ascii = 1; /* enable ascii tracing */

  global_init(CURL_GLOBAL_ALL);
  easy_init(curl);

  test_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
  test_setopt(curl, CURLOPT_DEBUGDATA, &config);
  /* the DEBUGFUNCTION has no effect until we enable VERBOSE */
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  /* setup repeated data string */
  for(i = 0; i < sizeof(databuf); ++i)
      databuf[i] = fill[i % sizeof fill];

  /* Post */
  test_setopt(curl, CURLOPT_POST, 1L);

#ifdef CURL_DOES_CONVERSIONS
  /* Convert the POST data to ASCII */
  test_setopt(curl, CURLOPT_TRANSFERTEXT, 1L);
#endif

  /* Setup read callback */
  test_setopt(curl, CURLOPT_POSTFIELDSIZE, (long) sizeof(databuf));
  test_setopt(curl, CURLOPT_READFUNCTION, read_callback);

  /* Write callback */
  test_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

  /* Ioctl function */
  test_setopt(curl, CURLOPT_IOCTLFUNCTION, ioctl_callback);

  test_setopt(curl, CURLOPT_PROXY, libtest_arg2);

  test_setopt(curl, CURLOPT_URL, URL);

  /* Accept any auth. But for this bug configure proxy with DIGEST, basic
     might work too, not NTLM */
  test_setopt(curl, CURLOPT_PROXYAUTH, (long)CURLAUTH_ANY);

  res = curl_easy_perform(curl);
  fprintf(stderr, "curl_easy_perform = %d\n", (int)res);

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();
  return (int)res;
}