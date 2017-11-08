int test(char *URL)
{
  CURL *curl;
  CURLcode res;
  int i;
  struct curl_slist *headerlist=NULL;

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  for (i = 0; i < NUM_HEADERS; i++) {
    int len;
    len = sprintf(buf, "Header%d: ", i);
    memset(&buf[len], 'A', SIZE_HEADERS);
    buf[len + SIZE_HEADERS]=0; /* zero terminate */
    headerlist = curl_slist_append(headerlist,  buf);
  }
  headerlist = curl_slist_append(headerlist, "Expect: ");

  curl_easy_setopt(curl, CURLOPT_URL, URL);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
  curl_easy_setopt(curl, CURLOPT_POST, 1);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, POSTLEN);
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(curl, CURLOPT_HEADER, 1);
  curl_easy_setopt(curl, CURLOPT_READFUNCTION, myreadfunc);
  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  curl_slist_free_all(headerlist);

  return (int)res;
}