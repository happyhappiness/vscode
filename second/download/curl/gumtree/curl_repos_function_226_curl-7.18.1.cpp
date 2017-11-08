int test(char *URL)
{
  CURLcode res;
  CURL *curl;
#ifndef LIB548
  int counter=0;
#endif

  if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
    fprintf(stderr, "curl_global_init() failed\n");
    return TEST_ERR_MAJOR_BAD;
  }

  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    curl_global_cleanup();
    return TEST_ERR_MAJOR_BAD;
  }

  curl_easy_setopt(curl, CURLOPT_URL, URL);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl, CURLOPT_HEADER, TRUE);
#ifdef LIB548
  /* set the data to POST with a mere pointer to a zero-terminated string */
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, UPLOADTHIS);
#else
  /* 547 style, which means reading the POST data from a callback */
  curl_easy_setopt(curl, CURLOPT_IOCTLFUNCTION, ioctlcallback);
  curl_easy_setopt(curl, CURLOPT_IOCTLDATA, &counter);
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, readcallback);
  curl_easy_setopt(curl, CURLOPT_READDATA, &counter);
  /* We CANNOT do the POST fine without setting the size (or choose chunked)! */
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(UPLOADTHIS));
#endif
  curl_easy_setopt(curl, CURLOPT_POST, 1);
  curl_easy_setopt(curl, CURLOPT_PROXY, libtest_arg2);
  curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, libtest_arg3);
  curl_easy_setopt(curl, CURLOPT_PROXYAUTH,
                   CURLAUTH_NTLM | CURLAUTH_DIGEST | CURLAUTH_BASIC );

  res = curl_easy_perform(curl);

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return (int)res;
}