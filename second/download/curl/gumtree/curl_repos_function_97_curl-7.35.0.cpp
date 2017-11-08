int
main(void)
{
  CURL *curl;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (curl) {
    char nline[256];

    curl_easy_setopt(curl, CURLOPT_URL, "http://www.example.com/");
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""); /* just to start the cookie engine */
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(res));
      return 1;
    }

    print_cookies(curl);

    printf("Erasing curl's knowledge of cookies!\n");
    curl_easy_setopt(curl, CURLOPT_COOKIELIST, "ALL");

    print_cookies(curl);

    printf("-----------------------------------------------\n"
           "Setting a cookie \"PREF\" via cookie interface:\n");
#ifdef WIN32
#define snprintf _snprintf
#endif
    /* Netscape format cookie */
    snprintf(nline, sizeof(nline), "%s\t%s\t%s\t%s\t%lu\t%s\t%s",
      ".google.com", "TRUE", "/", "FALSE", (unsigned long)time(NULL) + 31337UL, "PREF", "hello google, i like you very much!");
    res = curl_easy_setopt(curl, CURLOPT_COOKIELIST, nline);
    if (res != CURLE_OK) {
      fprintf(stderr, "Curl curl_easy_setopt failed: %s\n", curl_easy_strerror(res));
      return 1;
    }

    /* HTTP-header style cookie */
    snprintf(nline, sizeof(nline),
      "Set-Cookie: OLD_PREF=3d141414bf4209321; "
      "expires=Sun, 17-Jan-2038 19:14:07 GMT; path=/; domain=.google.com");
    res = curl_easy_setopt(curl, CURLOPT_COOKIELIST, nline);
    if (res != CURLE_OK) {
      fprintf(stderr, "Curl curl_easy_setopt failed: %s\n", curl_easy_strerror(res));
      return 1;
    }

    print_cookies(curl);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "Curl perform failed: %s\n", curl_easy_strerror(res));
      return 1;
    }
  }
  else {
    fprintf(stderr, "Curl init failed!\n");
    return 1;
  }

  curl_global_cleanup();
  return 0;
}