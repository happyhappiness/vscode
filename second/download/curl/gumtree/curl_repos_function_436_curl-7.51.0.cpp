int test(char *URL)
{
  CURLcode res;
  CURL *curl;

  if(curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  test_setopt(curl, CURLOPT_URL, URL);
  test_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
  test_setopt(curl, CURLOPT_VERBOSE, 1L);

  res = curl_easy_perform(curl);

  if(!res) {
    /* we are connected, now get a HTTP document the raw way */
    const char *request =
#ifdef CURL_DOES_CONVERSIONS
      /* ASCII representation with escape sequences for non-ASCII platforms */
      "\x47\x45\x54\x20\x2f\x35\x35\x36\x20\x48\x54\x54\x50\x2f\x31\x2e"
      "\x32\x0d\x0a\x48\x6f\x73\x74\x3a\x20\x6e\x69\x6e\x6a\x61\x0d\x0a"
      "\x0d\x0a";
#else
      "GET /556 HTTP/1.2\r\n"
      "Host: ninja\r\n\r\n";
#endif
    size_t iolen;
    char buf[1024];

    res = curl_easy_send(curl, request, strlen(request), &iolen);

    if(!res) {
      /* we assume that sending always work */
      size_t total=0;

      do {
        /* busy-read like crazy */
        res = curl_easy_recv(curl, buf, 1024, &iolen);

#ifdef TPF
        sleep(1); /* avoid ctl-10 dump */
#endif

        if(iolen) {
          /* send received stuff to stdout */
          if(!write(STDOUT_FILENO, buf, iolen))
            break;
        }
        total += iolen;

      } while(((res == CURLE_OK) || (res == CURLE_AGAIN)) && (total < 129));
    }
  }

test_cleanup:

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}