int main(void)
{
  CURL *curl;
  CURLcode res;
  struct data config;

  config.trace_ascii = 1; /* enable ascii tracing */

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);

    /* the DEBUGFUNCTION has no effect until we enable VERBOSE */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

    curl_easy_setopt(curl, CURLOPT_URL, "curl.haxx.se");
    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}