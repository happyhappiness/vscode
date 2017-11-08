int test(char *URL)
{
  CURL *curl;
  CURLcode res;
  struct data config;
  size_t i;
  char fill[] = "test data";

  config.trace_ascii = 1; /* enable ascii tracing */

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);
    /* the DEBUGFUNCTION has no effect until we enable VERBOSE */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

    /* setup repeated data string */
    for (i=0; i < sizeof data; ++i)
        data[i] = fill[i % sizeof fill];

    /* Post */
    curl_easy_setopt(curl, CURLOPT_POST, 1);

    /* Setup read callback */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, sizeof data);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

    /* Write callback */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    /* Ioctl function */
    curl_easy_setopt(curl, CURLOPT_IOCTLFUNCTION, ioctl_callback);

    curl_easy_setopt(curl, CURLOPT_PROXY, libtest_arg2);

    curl_easy_setopt(curl, CURLOPT_URL, URL);

    /* Accept any auth. But for this bug configure proxy with DIGEST, basic might work too, not NTLM */
    curl_easy_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_ANY);

    res = curl_easy_perform(curl);
    fprintf(stderr, "curl_easy_perform = %d\n", (int)res);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}