int test(char *URL)
{
  CURL *curl = NULL;
  CURL *dep = NULL;
  CURLSH *share = NULL;
  char errorbuffer[CURL_ERROR_SIZE];
  void *conv_from_network_cb = NULL;
  void *conv_to_network_cb = NULL;
  void *conv_from_utf8_cb = NULL;
  void *interleavecb = NULL;
  char *stringpointerextra=(char *)"moooo";
  struct curl_slist *slist=NULL;
  struct curl_httppost *httppost=NULL;
  FILE *stream = stderr;
  struct data object;
  char *charp;
  long val;
  curl_off_t oval;
  double dval;
  curl_socket_t sockfd;
  struct curl_certinfo *certinfo;
  struct curl_tlssessioninfo *tlssession;
  CURLcode res = CURLE_OK;
  (void)URL; /* not used */
  easy_init(dep);
  easy_init(curl);
  share = curl_share_init();
  if(!share) {
    res = CURLE_OUT_OF_MEMORY;
    goto test_cleanup;
  }

  res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &object);
  if(UNEX(res)) {
    err("WRITEDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
  if(UNEX(res)) {
    err("WRITEDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_URL, "string");
  if(UNEX(res)) {
    err("URL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_URL, NULL);
  if(UNEX(res)) {
    err("URL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PORT, 0L);
  if(UNEX(res)) {
    err("PORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PORT, 22L);
  if(UNEX(res)) {
    err("PORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PORT, LO);
  if(UNEX(res)) {
    err("PORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PORT, HI);
  if(UNEX(res)) {
    err("PORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY, "string");
  if(UNEX(res)) {
    err("PROXY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY, NULL);
  if(UNEX(res)) {
    err("PROXY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USERPWD, "string");
  if(UNEX(res)) {
    err("USERPWD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USERPWD, NULL);
  if(UNEX(res)) {
    err("USERPWD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "string");
  if(UNEX(res)) {
    err("PROXYUSERPWD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, NULL);
  if(UNEX(res)) {
    err("PROXYUSERPWD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RANGE, "string");
  if(UNEX(res)) {
    err("RANGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RANGE, NULL);
  if(UNEX(res)) {
    err("RANGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_READDATA, &object);
  if(UNEX(res)) {
    err("READDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_READDATA, NULL);
  if(UNEX(res)) {
    err("READDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuffer);
  if(UNEX(res)) {
    err("ERRORBUFFER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, NULL);
  if(UNEX(res)) {
    err("ERRORBUFFER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
                         writecb);
  if(UNEX(res)) {
    err("WRITEFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
  if(UNEX(res)) {
    err("WRITEFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_READFUNCTION,
                         readcb);
  if(UNEX(res)) {
    err("READFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
  if(UNEX(res)) {
    err("READFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, 0L);
  if(UNEX(res)) {
    err("TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, 22L);
  if(UNEX(res)) {
    err("TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, LO);
  if(UNEX(res)) {
    err("TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEOUT, HI);
  if(UNEX(res)) {
    err("TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INFILESIZE, 0L);
  if(UNEX(res)) {
    err("INFILESIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INFILESIZE, 22L);
  if(UNEX(res)) {
    err("INFILESIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INFILESIZE, LO);
  if(UNEX(res)) {
    err("INFILESIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INFILESIZE, HI);
  if(UNEX(res)) {
    err("INFILESIZE", res, __LINE__); goto test_cleanup; }
  (void)curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, stringpointerextra);
  if(UNEX(res)) {
    err("POSTFIELDS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, NULL);
  if(UNEX(res)) {
    err("POSTFIELDS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_REFERER, "string");
  if(UNEX(res)) {
    err("REFERER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_REFERER, NULL);
  if(UNEX(res)) {
    err("REFERER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTPPORT, "string");
  if(UNEX(res)) {
    err("FTPPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTPPORT, NULL);
  if(UNEX(res)) {
    err("FTPPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USERAGENT, "string");
  if(UNEX(res)) {
    err("USERAGENT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USERAGENT, NULL);
  if(UNEX(res)) {
    err("USERAGENT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 0L);
  if(UNEX(res)) {
    err("LOW_SPEED_LIMIT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 22L);
  if(UNEX(res)) {
    err("LOW_SPEED_LIMIT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, LO);
  if(UNEX(res)) {
    err("LOW_SPEED_LIMIT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, HI);
  if(UNEX(res)) {
    err("LOW_SPEED_LIMIT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 0L);
  if(UNEX(res)) {
    err("LOW_SPEED_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 22L);
  if(UNEX(res)) {
    err("LOW_SPEED_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, LO);
  if(UNEX(res)) {
    err("LOW_SPEED_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, HI);
  if(UNEX(res)) {
    err("LOW_SPEED_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESUME_FROM, 0L);
  if(UNEX(res)) {
    err("RESUME_FROM", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESUME_FROM, 22L);
  if(UNEX(res)) {
    err("RESUME_FROM", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESUME_FROM, LO);
  if(UNEX(res)) {
    err("RESUME_FROM", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESUME_FROM, HI);
  if(UNEX(res)) {
    err("RESUME_FROM", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIE, "string");
  if(UNEX(res)) {
    err("COOKIE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIE, NULL);
  if(UNEX(res)) {
    err("COOKIE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
  if(UNEX(res)) {
    err("HTTPHEADER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, NULL);
  if(UNEX(res)) {
    err("HTTPHEADER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPPOST, httppost);
  if(UNEX(res)) {
    err("HTTPPOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPPOST, NULL);
  if(UNEX(res)) {
    err("HTTPPOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLCERT, "string");
  if(UNEX(res)) {
    err("SSLCERT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLCERT, NULL);
  if(UNEX(res)) {
    err("SSLCERT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_KEYPASSWD, "string");
  if(UNEX(res)) {
    err("KEYPASSWD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_KEYPASSWD, NULL);
  if(UNEX(res)) {
    err("KEYPASSWD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CRLF, 0L);
  if(UNEX(res)) {
    err("CRLF", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CRLF, 22L);
  if(UNEX(res)) {
    err("CRLF", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CRLF, LO);
  if(UNEX(res)) {
    err("CRLF", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CRLF, HI);
  if(UNEX(res)) {
    err("CRLF", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_QUOTE, slist);
  if(UNEX(res)) {
    err("QUOTE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_QUOTE, NULL);
  if(UNEX(res)) {
    err("QUOTE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADERDATA, &object);
  if(UNEX(res)) {
    err("HEADERDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADERDATA, NULL);
  if(UNEX(res)) {
    err("HEADERDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "string");
  if(UNEX(res)) {
    err("COOKIEFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIEFILE, NULL);
  if(UNEX(res)) {
    err("COOKIEFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, 0L);
  if(UNEX(res)) {
    err("SSLVERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, 22L);
  if(UNEX(res)) {
    err("SSLVERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, LO);
  if(UNEX(res)) {
    err("SSLVERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLVERSION, HI);
  if(UNEX(res)) {
    err("SSLVERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMECONDITION, 0L);
  if(UNEX(res)) {
    err("TIMECONDITION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMECONDITION, 22L);
  if(UNEX(res)) {
    err("TIMECONDITION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMECONDITION, LO);
  if(UNEX(res)) {
    err("TIMECONDITION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMECONDITION, HI);
  if(UNEX(res)) {
    err("TIMECONDITION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEVALUE, 0L);
  if(UNEX(res)) {
    err("TIMEVALUE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEVALUE, 22L);
  if(UNEX(res)) {
    err("TIMEVALUE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEVALUE, LO);
  if(UNEX(res)) {
    err("TIMEVALUE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEVALUE, HI);
  if(UNEX(res)) {
    err("TIMEVALUE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "string");
  if(UNEX(res)) {
    err("CUSTOMREQUEST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, NULL);
  if(UNEX(res)) {
    err("CUSTOMREQUEST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STDERR, stream);
  if(UNEX(res)) {
    err("STDERR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STDERR, NULL);
  if(UNEX(res)) {
    err("STDERR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTQUOTE, slist);
  if(UNEX(res)) {
    err("POSTQUOTE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTQUOTE, NULL);
  if(UNEX(res)) {
    err("POSTQUOTE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OBSOLETE40, &object);
  if(UNEX(res)) {
    err("OBSOLETE40", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OBSOLETE40, NULL);
  if(UNEX(res)) {
    err("OBSOLETE40", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
  if(UNEX(res)) {
    err("VERBOSE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_VERBOSE, 22L);
  if(UNEX(res)) {
    err("VERBOSE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_VERBOSE, LO);
  if(UNEX(res)) {
    err("VERBOSE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_VERBOSE, HI);
  if(UNEX(res)) {
    err("VERBOSE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
  if(UNEX(res)) {
    err("HEADER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADER, 22L);
  if(UNEX(res)) {
    err("HEADER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADER, LO);
  if(UNEX(res)) {
    err("HEADER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADER, HI);
  if(UNEX(res)) {
    err("HEADER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
  if(UNEX(res)) {
    err("NOPROGRESS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 22L);
  if(UNEX(res)) {
    err("NOPROGRESS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, LO);
  if(UNEX(res)) {
    err("NOPROGRESS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, HI);
  if(UNEX(res)) {
    err("NOPROGRESS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
  if(UNEX(res)) {
    err("NOBODY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOBODY, 22L);
  if(UNEX(res)) {
    err("NOBODY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOBODY, LO);
  if(UNEX(res)) {
    err("NOBODY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOBODY, HI);
  if(UNEX(res)) {
    err("NOBODY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FAILONERROR, 0L);
  if(UNEX(res)) {
    err("FAILONERROR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FAILONERROR, 22L);
  if(UNEX(res)) {
    err("FAILONERROR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FAILONERROR, LO);
  if(UNEX(res)) {
    err("FAILONERROR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FAILONERROR, HI);
  if(UNEX(res)) {
    err("FAILONERROR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UPLOAD, 0L);
  if(UNEX(res)) {
    err("UPLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UPLOAD, 22L);
  if(UNEX(res)) {
    err("UPLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UPLOAD, LO);
  if(UNEX(res)) {
    err("UPLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UPLOAD, HI);
  if(UNEX(res)) {
    err("UPLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POST, 0L);
  if(UNEX(res)) {
    err("POST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POST, 22L);
  if(UNEX(res)) {
    err("POST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POST, LO);
  if(UNEX(res)) {
    err("POST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POST, HI);
  if(UNEX(res)) {
    err("POST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 0L);
  if(UNEX(res)) {
    err("DIRLISTONLY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, 22L);
  if(UNEX(res)) {
    err("DIRLISTONLY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, LO);
  if(UNEX(res)) {
    err("DIRLISTONLY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DIRLISTONLY, HI);
  if(UNEX(res)) {
    err("DIRLISTONLY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_APPEND, 0L);
  if(UNEX(res)) {
    err("APPEND", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_APPEND, 22L);
  if(UNEX(res)) {
    err("APPEND", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_APPEND, LO);
  if(UNEX(res)) {
    err("APPEND", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_APPEND, HI);
  if(UNEX(res)) {
    err("APPEND", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NETRC, 0L);
  if(UNEX(res)) {
    err("NETRC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NETRC, 22L);
  if(UNEX(res)) {
    err("NETRC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NETRC, LO);
  if(UNEX(res)) {
    err("NETRC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NETRC, HI);
  if(UNEX(res)) {
    err("NETRC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
  if(UNEX(res)) {
    err("FOLLOWLOCATION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 22L);
  if(UNEX(res)) {
    err("FOLLOWLOCATION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, LO);
  if(UNEX(res)) {
    err("FOLLOWLOCATION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, HI);
  if(UNEX(res)) {
    err("FOLLOWLOCATION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TRANSFERTEXT, 0L);
  if(UNEX(res)) {
    err("TRANSFERTEXT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TRANSFERTEXT, 22L);
  if(UNEX(res)) {
    err("TRANSFERTEXT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TRANSFERTEXT, LO);
  if(UNEX(res)) {
    err("TRANSFERTEXT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TRANSFERTEXT, HI);
  if(UNEX(res)) {
    err("TRANSFERTEXT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PUT, 0L);
  if(UNEX(res)) {
    err("PUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PUT, 22L);
  if(UNEX(res)) {
    err("PUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PUT, LO);
  if(UNEX(res)) {
    err("PUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PUT, HI);
  if(UNEX(res)) {
    err("PUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION,
                         progresscb);
  if(UNEX(res)) {
    err("PROGRESSFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, NULL);
  if(UNEX(res)) {
    err("PROGRESSFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &object);
  if(UNEX(res)) {
    err("PROGRESSDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, NULL);
  if(UNEX(res)) {
    err("PROGRESSDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 0L);
  if(UNEX(res)) {
    err("AUTOREFERER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 22L);
  if(UNEX(res)) {
    err("AUTOREFERER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_AUTOREFERER, LO);
  if(UNEX(res)) {
    err("AUTOREFERER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_AUTOREFERER, HI);
  if(UNEX(res)) {
    err("AUTOREFERER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYPORT, 0L);
  if(UNEX(res)) {
    err("PROXYPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYPORT, 22L);
  if(UNEX(res)) {
    err("PROXYPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYPORT, LO);
  if(UNEX(res)) {
    err("PROXYPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYPORT, HI);
  if(UNEX(res)) {
    err("PROXYPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0L);
  if(UNEX(res)) {
    err("POSTFIELDSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 22L);
  if(UNEX(res)) {
    err("POSTFIELDSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, LO);
  if(UNEX(res)) {
    err("POSTFIELDSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, HI);
  if(UNEX(res)) {
    err("POSTFIELDSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 0L);
  if(UNEX(res)) {
    err("HTTPPROXYTUNNEL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 22L);
  if(UNEX(res)) {
    err("HTTPPROXYTUNNEL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, LO);
  if(UNEX(res)) {
    err("HTTPPROXYTUNNEL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, HI);
  if(UNEX(res)) {
    err("HTTPPROXYTUNNEL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INTERFACE, "string");
  if(UNEX(res)) {
    err("INTERFACE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INTERFACE, NULL);
  if(UNEX(res)) {
    err("INTERFACE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_KRBLEVEL, "string");
  if(UNEX(res)) {
    err("KRBLEVEL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_KRBLEVEL, NULL);
  if(UNEX(res)) {
    err("KRBLEVEL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  if(UNEX(res)) {
    err("SSL_VERIFYPEER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 22L);
  if(UNEX(res)) {
    err("SSL_VERIFYPEER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, LO);
  if(UNEX(res)) {
    err("SSL_VERIFYPEER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, HI);
  if(UNEX(res)) {
    err("SSL_VERIFYPEER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CAINFO, "string");
  if(UNEX(res)) {
    err("CAINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CAINFO, NULL);
  if(UNEX(res)) {
    err("CAINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 0L);
  if(UNEX(res)) {
    err("MAXREDIRS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 22L);
  if(UNEX(res)) {
    err("MAXREDIRS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXREDIRS, LO);
  if(UNEX(res)) {
    err("MAXREDIRS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXREDIRS, HI);
  if(UNEX(res)) {
    err("MAXREDIRS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FILETIME, 0L);
  if(UNEX(res)) {
    err("FILETIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FILETIME, 22L);
  if(UNEX(res)) {
    err("FILETIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FILETIME, LO);
  if(UNEX(res)) {
    err("FILETIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FILETIME, HI);
  if(UNEX(res)) {
    err("FILETIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TELNETOPTIONS, slist);
  if(UNEX(res)) {
    err("TELNETOPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TELNETOPTIONS, NULL);
  if(UNEX(res)) {
    err("TELNETOPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXCONNECTS, 0L);
  if(UNEX(res)) {
    err("MAXCONNECTS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXCONNECTS, 22L);
  if(UNEX(res)) {
    err("MAXCONNECTS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXCONNECTS, LO);
  if(UNEX(res)) {
    err("MAXCONNECTS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXCONNECTS, HI);
  if(UNEX(res)) {
    err("MAXCONNECTS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OBSOLETE72, 0L);
  if(UNEX(res)) {
    err("OBSOLETE72", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OBSOLETE72, 22L);
  if(UNEX(res)) {
    err("OBSOLETE72", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OBSOLETE72, LO);
  if(UNEX(res)) {
    err("OBSOLETE72", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OBSOLETE72, HI);
  if(UNEX(res)) {
    err("OBSOLETE72", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, 0L);
  if(UNEX(res)) {
    err("FRESH_CONNECT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, 22L);
  if(UNEX(res)) {
    err("FRESH_CONNECT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, LO);
  if(UNEX(res)) {
    err("FRESH_CONNECT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FRESH_CONNECT, HI);
  if(UNEX(res)) {
    err("FRESH_CONNECT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 0L);
  if(UNEX(res)) {
    err("FORBID_REUSE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 22L);
  if(UNEX(res)) {
    err("FORBID_REUSE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, LO);
  if(UNEX(res)) {
    err("FORBID_REUSE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, HI);
  if(UNEX(res)) {
    err("FORBID_REUSE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RANDOM_FILE, "string");
  if(UNEX(res)) {
    err("RANDOM_FILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RANDOM_FILE, NULL);
  if(UNEX(res)) {
    err("RANDOM_FILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_EGDSOCKET, "string");
  if(UNEX(res)) {
    err("EGDSOCKET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_EGDSOCKET, NULL);
  if(UNEX(res)) {
    err("EGDSOCKET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 0L);
  if(UNEX(res)) {
    err("CONNECTTIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 22L);
  if(UNEX(res)) {
    err("CONNECTTIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, LO);
  if(UNEX(res)) {
    err("CONNECTTIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, HI);
  if(UNEX(res)) {
    err("CONNECTTIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION,
                         headercb);
  if(UNEX(res)) {
    err("HEADERFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
  if(UNEX(res)) {
    err("HEADERFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPGET, 0L);
  if(UNEX(res)) {
    err("HTTPGET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPGET, 22L);
  if(UNEX(res)) {
    err("HTTPGET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPGET, LO);
  if(UNEX(res)) {
    err("HTTPGET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPGET, HI);
  if(UNEX(res)) {
    err("HTTPGET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  if(UNEX(res)) {
    err("SSL_VERIFYHOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 22L);
  if(UNEX(res)) {
    err("SSL_VERIFYHOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, LO);
  if(UNEX(res)) {
    err("SSL_VERIFYHOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, HI);
  if(UNEX(res)) {
    err("SSL_VERIFYHOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "string");
  if(UNEX(res)) {
    err("COOKIEJAR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIEJAR, NULL);
  if(UNEX(res)) {
    err("COOKIEJAR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, "string");
  if(UNEX(res)) {
    err("SSL_CIPHER_LIST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, NULL);
  if(UNEX(res)) {
    err("SSL_CIPHER_LIST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, 0L);
  if(UNEX(res)) {
    err("HTTP_VERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, 22L);
  if(UNEX(res)) {
    err("HTTP_VERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, LO);
  if(UNEX(res)) {
    err("HTTP_VERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, HI);
  if(UNEX(res)) {
    err("HTTP_VERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, 0L);
  if(UNEX(res)) {
    err("FTP_USE_EPSV", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, 22L);
  if(UNEX(res)) {
    err("FTP_USE_EPSV", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, LO);
  if(UNEX(res)) {
    err("FTP_USE_EPSV", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, HI);
  if(UNEX(res)) {
    err("FTP_USE_EPSV", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "string");
  if(UNEX(res)) {
    err("SSLCERTTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, NULL);
  if(UNEX(res)) {
    err("SSLCERTTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLKEY, "string");
  if(UNEX(res)) {
    err("SSLKEY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLKEY, NULL);
  if(UNEX(res)) {
    err("SSLKEY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, "string");
  if(UNEX(res)) {
    err("SSLKEYTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, NULL);
  if(UNEX(res)) {
    err("SSLKEYTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLENGINE, "string");
  if(UNEX(res)) {
    err("SSLENGINE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLENGINE, NULL);
  if(UNEX(res)) {
    err("SSLENGINE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, 0L);
  if(UNEX(res)) {
    err("SSLENGINE_DEFAULT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, 22L);
  if(UNEX(res)) {
    err("SSLENGINE_DEFAULT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, LO);
  if(UNEX(res)) {
    err("SSLENGINE_DEFAULT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, HI);
  if(UNEX(res)) {
    err("SSLENGINE_DEFAULT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_USE_GLOBAL_CACHE, 0L);
  if(UNEX(res)) {
    err("DNS_USE_GLOBAL_CACHE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_USE_GLOBAL_CACHE, 22L);
  if(UNEX(res)) {
    err("DNS_USE_GLOBAL_CACHE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_USE_GLOBAL_CACHE, LO);
  if(UNEX(res)) {
    err("DNS_USE_GLOBAL_CACHE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_USE_GLOBAL_CACHE, HI);
  if(UNEX(res)) {
    err("DNS_USE_GLOBAL_CACHE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 0L);
  if(UNEX(res)) {
    err("DNS_CACHE_TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 22L);
  if(UNEX(res)) {
    err("DNS_CACHE_TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, LO);
  if(UNEX(res)) {
    err("DNS_CACHE_TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, HI);
  if(UNEX(res)) {
    err("DNS_CACHE_TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PREQUOTE, slist);
  if(UNEX(res)) {
    err("PREQUOTE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PREQUOTE, NULL);
  if(UNEX(res)) {
    err("PREQUOTE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,
                         debugcb);
  if(UNEX(res)) {
    err("DEBUGFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, NULL);
  if(UNEX(res)) {
    err("DEBUGFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &object);
  if(UNEX(res)) {
    err("DEBUGDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DEBUGDATA, NULL);
  if(UNEX(res)) {
    err("DEBUGDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 0L);
  if(UNEX(res)) {
    err("COOKIESESSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIESESSION, 22L);
  if(UNEX(res)) {
    err("COOKIESESSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIESESSION, LO);
  if(UNEX(res)) {
    err("COOKIESESSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIESESSION, HI);
  if(UNEX(res)) {
    err("COOKIESESSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CAPATH, "string");
  if(UNEX(res)) {
    err("CAPATH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CAPATH, NULL);
  if(UNEX(res)) {
    err("CAPATH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 0L);
  if(UNEX(res)) {
    err("BUFFERSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 22L);
  if(UNEX(res)) {
    err("BUFFERSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, LO);
  if(UNEX(res)) {
    err("BUFFERSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, HI);
  if(UNEX(res)) {
    err("BUFFERSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 0L);
  if(UNEX(res)) {
    err("NOSIGNAL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 22L);
  if(UNEX(res)) {
    err("NOSIGNAL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, LO);
  if(UNEX(res)) {
    err("NOSIGNAL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOSIGNAL, HI);
  if(UNEX(res)) {
    err("NOSIGNAL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SHARE, share);
  if(UNEX(res)) {
    err("SHARE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SHARE, NULL);
  if(UNEX(res)) {
    err("SHARE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYTYPE, 0L);
  if(UNEX(res)) {
    err("PROXYTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYTYPE, 22L);
  if(UNEX(res)) {
    err("PROXYTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYTYPE, LO);
  if(UNEX(res)) {
    err("PROXYTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYTYPE, HI);
  if(UNEX(res)) {
    err("PROXYTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "string");
  if(UNEX(res)) {
    err("ACCEPT_ENCODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, NULL);
  if(UNEX(res)) {
    err("ACCEPT_ENCODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PRIVATE, &object);
  if(UNEX(res)) {
    err("PRIVATE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PRIVATE, NULL);
  if(UNEX(res)) {
    err("PRIVATE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP200ALIASES, slist);
  if(UNEX(res)) {
    err("HTTP200ALIASES", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP200ALIASES, NULL);
  if(UNEX(res)) {
    err("HTTP200ALIASES", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UNRESTRICTED_AUTH, 0L);
  if(UNEX(res)) {
    err("UNRESTRICTED_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UNRESTRICTED_AUTH, 22L);
  if(UNEX(res)) {
    err("UNRESTRICTED_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UNRESTRICTED_AUTH, LO);
  if(UNEX(res)) {
    err("UNRESTRICTED_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UNRESTRICTED_AUTH, HI);
  if(UNEX(res)) {
    err("UNRESTRICTED_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_EPRT, 0L);
  if(UNEX(res)) {
    err("FTP_USE_EPRT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_EPRT, 22L);
  if(UNEX(res)) {
    err("FTP_USE_EPRT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_EPRT, LO);
  if(UNEX(res)) {
    err("FTP_USE_EPRT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_EPRT, HI);
  if(UNEX(res)) {
    err("FTP_USE_EPRT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPAUTH, 0L);
  if(UNEX(res)) {
    err("HTTPAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPAUTH, 22L);
  if(UNEX(res)) {
    err("HTTPAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPAUTH, LO);
  if(UNEX(res)) {
    err("HTTPAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTPAUTH, HI);
  if(UNEX(res)) {
    err("HTTPAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION,
                         ssl_ctx_cb);
  if(UNEX(res)) {
    err("SSL_CTX_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, NULL);
  if(UNEX(res)) {
    err("SSL_CTX_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_CTX_DATA, &object);
  if(UNEX(res)) {
    err("SSL_CTX_DATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_CTX_DATA, NULL);
  if(UNEX(res)) {
    err("SSL_CTX_DATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS, 0L);
  if(UNEX(res)) {
    err("FTP_CREATE_MISSING_DIRS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS, 22L);
  if(UNEX(res)) {
    err("FTP_CREATE_MISSING_DIRS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS, LO);
  if(UNEX(res)) {
    err("FTP_CREATE_MISSING_DIRS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_CREATE_MISSING_DIRS, HI);
  if(UNEX(res)) {
    err("FTP_CREATE_MISSING_DIRS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYAUTH, 0L);
  if(UNEX(res)) {
    err("PROXYAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYAUTH, 22L);
  if(UNEX(res)) {
    err("PROXYAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYAUTH, LO);
  if(UNEX(res)) {
    err("PROXYAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYAUTH, HI);
  if(UNEX(res)) {
    err("PROXYAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 0L);
  if(UNEX(res)) {
    err("FTP_RESPONSE_TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 22L);
  if(UNEX(res)) {
    err("FTP_RESPONSE_TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, LO);
  if(UNEX(res)) {
    err("FTP_RESPONSE_TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, HI);
  if(UNEX(res)) {
    err("FTP_RESPONSE_TIMEOUT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IPRESOLVE, 0L);
  if(UNEX(res)) {
    err("IPRESOLVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IPRESOLVE, 22L);
  if(UNEX(res)) {
    err("IPRESOLVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IPRESOLVE, LO);
  if(UNEX(res)) {
    err("IPRESOLVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IPRESOLVE, HI);
  if(UNEX(res)) {
    err("IPRESOLVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, 0L);
  if(UNEX(res)) {
    err("MAXFILESIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, 22L);
  if(UNEX(res)) {
    err("MAXFILESIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, LO);
  if(UNEX(res)) {
    err("MAXFILESIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXFILESIZE, HI);
  if(UNEX(res)) {
    err("MAXFILESIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, OFF_NO);
  if(UNEX(res)) {
    err("INFILESIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, OFF_HI);
  if(UNEX(res)) {
    err("INFILESIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, OFF_LO);
  if(UNEX(res)) {
    err("INFILESIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESUME_FROM_LARGE, OFF_NO);
  if(UNEX(res)) {
    err("RESUME_FROM_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESUME_FROM_LARGE, OFF_HI);
  if(UNEX(res)) {
    err("RESUME_FROM_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESUME_FROM_LARGE, OFF_LO);
  if(UNEX(res)) {
    err("RESUME_FROM_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXFILESIZE_LARGE, OFF_NO);
  if(UNEX(res)) {
    err("MAXFILESIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXFILESIZE_LARGE, OFF_HI);
  if(UNEX(res)) {
    err("MAXFILESIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAXFILESIZE_LARGE, OFF_LO);
  if(UNEX(res)) {
    err("MAXFILESIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NETRC_FILE, "string");
  if(UNEX(res)) {
    err("NETRC_FILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NETRC_FILE, NULL);
  if(UNEX(res)) {
    err("NETRC_FILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USE_SSL, 0L);
  if(UNEX(res)) {
    err("USE_SSL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USE_SSL, 22L);
  if(UNEX(res)) {
    err("USE_SSL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USE_SSL, LO);
  if(UNEX(res)) {
    err("USE_SSL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USE_SSL, HI);
  if(UNEX(res)) {
    err("USE_SSL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, OFF_NO);
  if(UNEX(res)) {
    err("POSTFIELDSIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, OFF_HI);
  if(UNEX(res)) {
    err("POSTFIELDSIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, OFF_LO);
  if(UNEX(res)) {
    err("POSTFIELDSIZE_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, 0L);
  if(UNEX(res)) {
    err("TCP_NODELAY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, 22L);
  if(UNEX(res)) {
    err("TCP_NODELAY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, LO);
  if(UNEX(res)) {
    err("TCP_NODELAY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_NODELAY, HI);
  if(UNEX(res)) {
    err("TCP_NODELAY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTPSSLAUTH, 0L);
  if(UNEX(res)) {
    err("FTPSSLAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTPSSLAUTH, 22L);
  if(UNEX(res)) {
    err("FTPSSLAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTPSSLAUTH, LO);
  if(UNEX(res)) {
    err("FTPSSLAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTPSSLAUTH, HI);
  if(UNEX(res)) {
    err("FTPSSLAUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IOCTLFUNCTION,
                         ioctlcb);
  if(UNEX(res)) {
    err("IOCTLFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IOCTLFUNCTION, NULL);
  if(UNEX(res)) {
    err("IOCTLFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IOCTLDATA, &object);
  if(UNEX(res)) {
    err("IOCTLDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IOCTLDATA, NULL);
  if(UNEX(res)) {
    err("IOCTLDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_ACCOUNT, "string");
  if(UNEX(res)) {
    err("FTP_ACCOUNT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_ACCOUNT, NULL);
  if(UNEX(res)) {
    err("FTP_ACCOUNT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIELIST, "string");
  if(UNEX(res)) {
    err("COOKIELIST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COOKIELIST, NULL);
  if(UNEX(res)) {
    err("COOKIELIST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, 0L);
  if(UNEX(res)) {
    err("IGNORE_CONTENT_LENGTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, 22L);
  if(UNEX(res)) {
    err("IGNORE_CONTENT_LENGTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, LO);
  if(UNEX(res)) {
    err("IGNORE_CONTENT_LENGTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_IGNORE_CONTENT_LENGTH, HI);
  if(UNEX(res)) {
    err("IGNORE_CONTENT_LENGTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, 0L);
  if(UNEX(res)) {
    err("FTP_SKIP_PASV_IP", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, 22L);
  if(UNEX(res)) {
    err("FTP_SKIP_PASV_IP", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, LO);
  if(UNEX(res)) {
    err("FTP_SKIP_PASV_IP", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_SKIP_PASV_IP, HI);
  if(UNEX(res)) {
    err("FTP_SKIP_PASV_IP", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_FILEMETHOD, 0L);
  if(UNEX(res)) {
    err("FTP_FILEMETHOD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_FILEMETHOD, 22L);
  if(UNEX(res)) {
    err("FTP_FILEMETHOD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_FILEMETHOD, LO);
  if(UNEX(res)) {
    err("FTP_FILEMETHOD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_FILEMETHOD, HI);
  if(UNEX(res)) {
    err("FTP_FILEMETHOD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOCALPORT, 0L);
  if(UNEX(res)) {
    err("LOCALPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOCALPORT, 22L);
  if(UNEX(res)) {
    err("LOCALPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOCALPORT, LO);
  if(UNEX(res)) {
    err("LOCALPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOCALPORT, HI);
  if(UNEX(res)) {
    err("LOCALPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOCALPORTRANGE, 0L);
  if(UNEX(res)) {
    err("LOCALPORTRANGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOCALPORTRANGE, 22L);
  if(UNEX(res)) {
    err("LOCALPORTRANGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOCALPORTRANGE, LO);
  if(UNEX(res)) {
    err("LOCALPORTRANGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOCALPORTRANGE, HI);
  if(UNEX(res)) {
    err("LOCALPORTRANGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 0L);
  if(UNEX(res)) {
    err("CONNECT_ONLY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 22L);
  if(UNEX(res)) {
    err("CONNECT_ONLY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, LO);
  if(UNEX(res)) {
    err("CONNECT_ONLY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, HI);
  if(UNEX(res)) {
    err("CONNECT_ONLY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_FUNCTION,
                         conv_from_network_cb);
  if(UNEX(res)) {
    err("CONV_FROM_NETWORK_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONV_FROM_NETWORK_FUNCTION, NULL);
  if(UNEX(res)) {
    err("CONV_FROM_NETWORK_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONV_TO_NETWORK_FUNCTION,
                         conv_to_network_cb);
  if(UNEX(res)) {
    err("CONV_TO_NETWORK_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONV_TO_NETWORK_FUNCTION, NULL);
  if(UNEX(res)) {
    err("CONV_TO_NETWORK_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_FUNCTION,
                         conv_from_utf8_cb);
  if(UNEX(res)) {
    err("CONV_FROM_UTF8_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONV_FROM_UTF8_FUNCTION, NULL);
  if(UNEX(res)) {
    err("CONV_FROM_UTF8_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE, OFF_NO);
  if(UNEX(res)) {
    err("MAX_SEND_SPEED_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE, OFF_HI);
  if(UNEX(res)) {
    err("MAX_SEND_SPEED_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE, OFF_LO);
  if(UNEX(res)) {
    err("MAX_SEND_SPEED_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, OFF_NO);
  if(UNEX(res)) {
    err("MAX_RECV_SPEED_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, OFF_HI);
  if(UNEX(res)) {
    err("MAX_RECV_SPEED_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, OFF_LO);
  if(UNEX(res)) {
    err("MAX_RECV_SPEED_LARGE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_ALTERNATIVE_TO_USER, "string");
  if(UNEX(res)) {
    err("FTP_ALTERNATIVE_TO_USER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_ALTERNATIVE_TO_USER, NULL);
  if(UNEX(res)) {
    err("FTP_ALTERNATIVE_TO_USER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION,
                         sockoptcb);
  if(UNEX(res)) {
    err("SOCKOPTFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKOPTFUNCTION, NULL);
  if(UNEX(res)) {
    err("SOCKOPTFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKOPTDATA, &object);
  if(UNEX(res)) {
    err("SOCKOPTDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKOPTDATA, NULL);
  if(UNEX(res)) {
    err("SOCKOPTDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_SESSIONID_CACHE, 0L);
  if(UNEX(res)) {
    err("SSL_SESSIONID_CACHE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_SESSIONID_CACHE, 22L);
  if(UNEX(res)) {
    err("SSL_SESSIONID_CACHE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_SESSIONID_CACHE, LO);
  if(UNEX(res)) {
    err("SSL_SESSIONID_CACHE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_SESSIONID_CACHE, HI);
  if(UNEX(res)) {
    err("SSL_SESSIONID_CACHE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, 0L);
  if(UNEX(res)) {
    err("SSH_AUTH_TYPES", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, 22L);
  if(UNEX(res)) {
    err("SSH_AUTH_TYPES", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, LO);
  if(UNEX(res)) {
    err("SSH_AUTH_TYPES", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_AUTH_TYPES, HI);
  if(UNEX(res)) {
    err("SSH_AUTH_TYPES", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_PUBLIC_KEYFILE, "string");
  if(UNEX(res)) {
    err("SSH_PUBLIC_KEYFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_PUBLIC_KEYFILE, NULL);
  if(UNEX(res)) {
    err("SSH_PUBLIC_KEYFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_PRIVATE_KEYFILE, "string");
  if(UNEX(res)) {
    err("SSH_PRIVATE_KEYFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_PRIVATE_KEYFILE, NULL);
  if(UNEX(res)) {
    err("SSH_PRIVATE_KEYFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_SSL_CCC, 0L);
  if(UNEX(res)) {
    err("FTP_SSL_CCC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_SSL_CCC, 22L);
  if(UNEX(res)) {
    err("FTP_SSL_CCC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_SSL_CCC, LO);
  if(UNEX(res)) {
    err("FTP_SSL_CCC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_SSL_CCC, HI);
  if(UNEX(res)) {
    err("FTP_SSL_CCC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 0L);
  if(UNEX(res)) {
    err("TIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 22L);
  if(UNEX(res)) {
    err("TIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, LO);
  if(UNEX(res)) {
    err("TIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, HI);
  if(UNEX(res)) {
    err("TIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 0L);
  if(UNEX(res)) {
    err("CONNECTTIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, 22L);
  if(UNEX(res)) {
    err("CONNECTTIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, LO);
  if(UNEX(res)) {
    err("CONNECTTIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, HI);
  if(UNEX(res)) {
    err("CONNECTTIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_TRANSFER_DECODING, 0L);
  if(UNEX(res)) {
    err("HTTP_TRANSFER_DECODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_TRANSFER_DECODING, 22L);
  if(UNEX(res)) {
    err("HTTP_TRANSFER_DECODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_TRANSFER_DECODING, LO);
  if(UNEX(res)) {
    err("HTTP_TRANSFER_DECODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_TRANSFER_DECODING, HI);
  if(UNEX(res)) {
    err("HTTP_TRANSFER_DECODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, 0L);
  if(UNEX(res)) {
    err("HTTP_CONTENT_DECODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, 22L);
  if(UNEX(res)) {
    err("HTTP_CONTENT_DECODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, LO);
  if(UNEX(res)) {
    err("HTTP_CONTENT_DECODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HTTP_CONTENT_DECODING, HI);
  if(UNEX(res)) {
    err("HTTP_CONTENT_DECODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NEW_FILE_PERMS, 0L);
  if(UNEX(res)) {
    err("NEW_FILE_PERMS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NEW_FILE_PERMS, 22L);
  if(UNEX(res)) {
    err("NEW_FILE_PERMS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NEW_FILE_PERMS, LO);
  if(UNEX(res)) {
    err("NEW_FILE_PERMS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NEW_FILE_PERMS, HI);
  if(UNEX(res)) {
    err("NEW_FILE_PERMS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NEW_DIRECTORY_PERMS, 0L);
  if(UNEX(res)) {
    err("NEW_DIRECTORY_PERMS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NEW_DIRECTORY_PERMS, 22L);
  if(UNEX(res)) {
    err("NEW_DIRECTORY_PERMS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NEW_DIRECTORY_PERMS, LO);
  if(UNEX(res)) {
    err("NEW_DIRECTORY_PERMS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NEW_DIRECTORY_PERMS, HI);
  if(UNEX(res)) {
    err("NEW_DIRECTORY_PERMS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTREDIR, 0L);
  if(UNEX(res)) {
    err("POSTREDIR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTREDIR, 22L);
  if(UNEX(res)) {
    err("POSTREDIR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTREDIR, LO);
  if(UNEX(res)) {
    err("POSTREDIR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_POSTREDIR, HI);
  if(UNEX(res)) {
    err("POSTREDIR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_HOST_PUBLIC_KEY_MD5, "string");
  if(UNEX(res)) {
    err("SSH_HOST_PUBLIC_KEY_MD5", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_HOST_PUBLIC_KEY_MD5, NULL);
  if(UNEX(res)) {
    err("SSH_HOST_PUBLIC_KEY_MD5", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION,
                         opensocketcb);
  if(UNEX(res)) {
    err("OPENSOCKETFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, NULL);
  if(UNEX(res)) {
    err("OPENSOCKETFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, &object);
  if(UNEX(res)) {
    err("OPENSOCKETDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_OPENSOCKETDATA, NULL);
  if(UNEX(res)) {
    err("OPENSOCKETDATA", res, __LINE__); goto test_cleanup; }
  (void)curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, 0);
  res = curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, stringpointerextra);
  if(UNEX(res)) {
    err("COPYPOSTFIELDS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, NULL);
  if(UNEX(res)) {
    err("COPYPOSTFIELDS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TRANSFER_MODE, 0L);
  if(UNEX(res)) {
    err("PROXY_TRANSFER_MODE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TRANSFER_MODE, 22L);
  if(UNEX(res)) {
    err("PROXY_TRANSFER_MODE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TRANSFER_MODE, LO);
  if(UNEX(res)) {
    err("PROXY_TRANSFER_MODE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TRANSFER_MODE, HI);
  if(UNEX(res)) {
    err("PROXY_TRANSFER_MODE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SEEKFUNCTION,
                         seekcb);
  if(UNEX(res)) {
    err("SEEKFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SEEKFUNCTION, NULL);
  if(UNEX(res)) {
    err("SEEKFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SEEKDATA, &object);
  if(UNEX(res)) {
    err("SEEKDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SEEKDATA, NULL);
  if(UNEX(res)) {
    err("SEEKDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CRLFILE, "string");
  if(UNEX(res)) {
    err("CRLFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CRLFILE, NULL);
  if(UNEX(res)) {
    err("CRLFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ISSUERCERT, "string");
  if(UNEX(res)) {
    err("ISSUERCERT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ISSUERCERT, NULL);
  if(UNEX(res)) {
    err("ISSUERCERT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ADDRESS_SCOPE, 0L);
  if(UNEX(res)) {
    err("ADDRESS_SCOPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ADDRESS_SCOPE, 22L);
  if(UNEX(res)) {
    err("ADDRESS_SCOPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ADDRESS_SCOPE, LO);
  if(UNEX(res)) {
    err("ADDRESS_SCOPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ADDRESS_SCOPE, HI);
  if(UNEX(res)) {
    err("ADDRESS_SCOPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CERTINFO, 0L);
  if(UNEX(res)) {
    err("CERTINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CERTINFO, 22L);
  if(UNEX(res)) {
    err("CERTINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CERTINFO, LO);
  if(UNEX(res)) {
    err("CERTINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CERTINFO, HI);
  if(UNEX(res)) {
    err("CERTINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USERNAME, "string");
  if(UNEX(res)) {
    err("USERNAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_USERNAME, NULL);
  if(UNEX(res)) {
    err("USERNAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PASSWORD, "string");
  if(UNEX(res)) {
    err("PASSWORD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PASSWORD, NULL);
  if(UNEX(res)) {
    err("PASSWORD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYUSERNAME, "string");
  if(UNEX(res)) {
    err("PROXYUSERNAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYUSERNAME, NULL);
  if(UNEX(res)) {
    err("PROXYUSERNAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD, "string");
  if(UNEX(res)) {
    err("PROXYPASSWORD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD, NULL);
  if(UNEX(res)) {
    err("PROXYPASSWORD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOPROXY, "string");
  if(UNEX(res)) {
    err("NOPROXY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_NOPROXY, NULL);
  if(UNEX(res)) {
    err("NOPROXY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TFTP_BLKSIZE, 0L);
  if(UNEX(res)) {
    err("TFTP_BLKSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TFTP_BLKSIZE, 22L);
  if(UNEX(res)) {
    err("TFTP_BLKSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TFTP_BLKSIZE, LO);
  if(UNEX(res)) {
    err("TFTP_BLKSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TFTP_BLKSIZE, HI);
  if(UNEX(res)) {
    err("TFTP_BLKSIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_GSSAPI_SERVICE, "string");
  if(UNEX(res)) {
    err("SOCKS5_GSSAPI_SERVICE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_GSSAPI_SERVICE, NULL);
  if(UNEX(res)) {
    err("SOCKS5_GSSAPI_SERVICE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_GSSAPI_NEC, 0L);
  if(UNEX(res)) {
    err("SOCKS5_GSSAPI_NEC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_GSSAPI_NEC, 22L);
  if(UNEX(res)) {
    err("SOCKS5_GSSAPI_NEC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_GSSAPI_NEC, LO);
  if(UNEX(res)) {
    err("SOCKS5_GSSAPI_NEC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_GSSAPI_NEC, HI);
  if(UNEX(res)) {
    err("SOCKS5_GSSAPI_NEC", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROTOCOLS, 0L);
  if(UNEX(res)) {
    err("PROTOCOLS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROTOCOLS, 22L);
  if(UNEX(res)) {
    err("PROTOCOLS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROTOCOLS, LO);
  if(UNEX(res)) {
    err("PROTOCOLS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROTOCOLS, HI);
  if(UNEX(res)) {
    err("PROTOCOLS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS, 0L);
  if(UNEX(res)) {
    err("REDIR_PROTOCOLS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS, 22L);
  if(UNEX(res)) {
    err("REDIR_PROTOCOLS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS, LO);
  if(UNEX(res)) {
    err("REDIR_PROTOCOLS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS, HI);
  if(UNEX(res)) {
    err("REDIR_PROTOCOLS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_KNOWNHOSTS, "string");
  if(UNEX(res)) {
    err("SSH_KNOWNHOSTS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_KNOWNHOSTS, NULL);
  if(UNEX(res)) {
    err("SSH_KNOWNHOSTS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_KEYFUNCTION,
                         ssh_keycb);
  if(UNEX(res)) {
    err("SSH_KEYFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_KEYFUNCTION, NULL);
  if(UNEX(res)) {
    err("SSH_KEYFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_KEYDATA, &object);
  if(UNEX(res)) {
    err("SSH_KEYDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSH_KEYDATA, NULL);
  if(UNEX(res)) {
    err("SSH_KEYDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "string");
  if(UNEX(res)) {
    err("MAIL_FROM", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAIL_FROM, NULL);
  if(UNEX(res)) {
    err("MAIL_FROM", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, slist);
  if(UNEX(res)) {
    err("MAIL_RCPT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, NULL);
  if(UNEX(res)) {
    err("MAIL_RCPT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_PRET, 0L);
  if(UNEX(res)) {
    err("FTP_USE_PRET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_PRET, 22L);
  if(UNEX(res)) {
    err("FTP_USE_PRET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_PRET, LO);
  if(UNEX(res)) {
    err("FTP_USE_PRET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FTP_USE_PRET, HI);
  if(UNEX(res)) {
    err("FTP_USE_PRET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, 0L);
  if(UNEX(res)) {
    err("RTSP_REQUEST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, 22L);
  if(UNEX(res)) {
    err("RTSP_REQUEST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, LO);
  if(UNEX(res)) {
    err("RTSP_REQUEST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_REQUEST, HI);
  if(UNEX(res)) {
    err("RTSP_REQUEST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_SESSION_ID, "string");
  if(UNEX(res)) {
    err("RTSP_SESSION_ID", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_SESSION_ID, NULL);
  if(UNEX(res)) {
    err("RTSP_SESSION_ID", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_STREAM_URI, "string");
  if(UNEX(res)) {
    err("RTSP_STREAM_URI", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_STREAM_URI, NULL);
  if(UNEX(res)) {
    err("RTSP_STREAM_URI", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_TRANSPORT, "string");
  if(UNEX(res)) {
    err("RTSP_TRANSPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_TRANSPORT, NULL);
  if(UNEX(res)) {
    err("RTSP_TRANSPORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_CLIENT_CSEQ, 0L);
  if(UNEX(res)) {
    err("RTSP_CLIENT_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_CLIENT_CSEQ, 22L);
  if(UNEX(res)) {
    err("RTSP_CLIENT_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_CLIENT_CSEQ, LO);
  if(UNEX(res)) {
    err("RTSP_CLIENT_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_CLIENT_CSEQ, HI);
  if(UNEX(res)) {
    err("RTSP_CLIENT_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_SERVER_CSEQ, 0L);
  if(UNEX(res)) {
    err("RTSP_SERVER_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_SERVER_CSEQ, 22L);
  if(UNEX(res)) {
    err("RTSP_SERVER_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_SERVER_CSEQ, LO);
  if(UNEX(res)) {
    err("RTSP_SERVER_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RTSP_SERVER_CSEQ, HI);
  if(UNEX(res)) {
    err("RTSP_SERVER_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INTERLEAVEDATA, &object);
  if(UNEX(res)) {
    err("INTERLEAVEDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INTERLEAVEDATA, NULL);
  if(UNEX(res)) {
    err("INTERLEAVEDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INTERLEAVEFUNCTION,
                         interleavecb);
  if(UNEX(res)) {
    err("INTERLEAVEFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_INTERLEAVEFUNCTION, NULL);
  if(UNEX(res)) {
    err("INTERLEAVEFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_WILDCARDMATCH, 0L);
  if(UNEX(res)) {
    err("WILDCARDMATCH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_WILDCARDMATCH, 22L);
  if(UNEX(res)) {
    err("WILDCARDMATCH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_WILDCARDMATCH, LO);
  if(UNEX(res)) {
    err("WILDCARDMATCH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_WILDCARDMATCH, HI);
  if(UNEX(res)) {
    err("WILDCARDMATCH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CHUNK_BGN_FUNCTION,
                         chunk_bgn_cb);
  if(UNEX(res)) {
    err("CHUNK_BGN_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CHUNK_BGN_FUNCTION, NULL);
  if(UNEX(res)) {
    err("CHUNK_BGN_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CHUNK_END_FUNCTION,
                         chunk_end_cb);
  if(UNEX(res)) {
    err("CHUNK_END_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CHUNK_END_FUNCTION, NULL);
  if(UNEX(res)) {
    err("CHUNK_END_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FNMATCH_FUNCTION,
                         fnmatch_cb);
  if(UNEX(res)) {
    err("FNMATCH_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FNMATCH_FUNCTION, NULL);
  if(UNEX(res)) {
    err("FNMATCH_FUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CHUNK_DATA, &object);
  if(UNEX(res)) {
    err("CHUNK_DATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CHUNK_DATA, NULL);
  if(UNEX(res)) {
    err("CHUNK_DATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FNMATCH_DATA, &object);
  if(UNEX(res)) {
    err("FNMATCH_DATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_FNMATCH_DATA, NULL);
  if(UNEX(res)) {
    err("FNMATCH_DATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESOLVE, slist);
  if(UNEX(res)) {
    err("RESOLVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_RESOLVE, NULL);
  if(UNEX(res)) {
    err("RESOLVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TLSAUTH_USERNAME, "string");
  if(UNEX(res)) {
    err("TLSAUTH_USERNAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TLSAUTH_USERNAME, NULL);
  if(UNEX(res)) {
    err("TLSAUTH_USERNAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TLSAUTH_PASSWORD, "string");
  if(UNEX(res)) {
    err("TLSAUTH_PASSWORD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TLSAUTH_PASSWORD, NULL);
  if(UNEX(res)) {
    err("TLSAUTH_PASSWORD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TLSAUTH_TYPE, "string");
  if(UNEX(res)) {
    err("TLSAUTH_TYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TLSAUTH_TYPE, NULL);
  if(UNEX(res)) {
    err("TLSAUTH_TYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TRANSFER_ENCODING, 0L);
  if(UNEX(res)) {
    err("TRANSFER_ENCODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TRANSFER_ENCODING, 22L);
  if(UNEX(res)) {
    err("TRANSFER_ENCODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TRANSFER_ENCODING, LO);
  if(UNEX(res)) {
    err("TRANSFER_ENCODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TRANSFER_ENCODING, HI);
  if(UNEX(res)) {
    err("TRANSFER_ENCODING", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CLOSESOCKETFUNCTION,
                         closesocketcb);
  if(UNEX(res)) {
    err("CLOSESOCKETFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CLOSESOCKETFUNCTION, NULL);
  if(UNEX(res)) {
    err("CLOSESOCKETFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CLOSESOCKETDATA, &object);
  if(UNEX(res)) {
    err("CLOSESOCKETDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CLOSESOCKETDATA, NULL);
  if(UNEX(res)) {
    err("CLOSESOCKETDATA", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_GSSAPI_DELEGATION, 0L);
  if(UNEX(res)) {
    err("GSSAPI_DELEGATION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_GSSAPI_DELEGATION, 22L);
  if(UNEX(res)) {
    err("GSSAPI_DELEGATION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_GSSAPI_DELEGATION, LO);
  if(UNEX(res)) {
    err("GSSAPI_DELEGATION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_GSSAPI_DELEGATION, HI);
  if(UNEX(res)) {
    err("GSSAPI_DELEGATION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, "string");
  if(UNEX(res)) {
    err("DNS_SERVERS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, NULL);
  if(UNEX(res)) {
    err("DNS_SERVERS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ACCEPTTIMEOUT_MS, 0L);
  if(UNEX(res)) {
    err("ACCEPTTIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ACCEPTTIMEOUT_MS, 22L);
  if(UNEX(res)) {
    err("ACCEPTTIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ACCEPTTIMEOUT_MS, LO);
  if(UNEX(res)) {
    err("ACCEPTTIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ACCEPTTIMEOUT_MS, HI);
  if(UNEX(res)) {
    err("ACCEPTTIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L);
  if(UNEX(res)) {
    err("TCP_KEEPALIVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 22L);
  if(UNEX(res)) {
    err("TCP_KEEPALIVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, LO);
  if(UNEX(res)) {
    err("TCP_KEEPALIVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, HI);
  if(UNEX(res)) {
    err("TCP_KEEPALIVE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 0L);
  if(UNEX(res)) {
    err("TCP_KEEPIDLE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, 22L);
  if(UNEX(res)) {
    err("TCP_KEEPIDLE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, LO);
  if(UNEX(res)) {
    err("TCP_KEEPIDLE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPIDLE, HI);
  if(UNEX(res)) {
    err("TCP_KEEPIDLE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 0L);
  if(UNEX(res)) {
    err("TCP_KEEPINTVL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, 22L);
  if(UNEX(res)) {
    err("TCP_KEEPINTVL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, LO);
  if(UNEX(res)) {
    err("TCP_KEEPINTVL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_KEEPINTVL, HI);
  if(UNEX(res)) {
    err("TCP_KEEPINTVL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, 0L);
  if(UNEX(res)) {
    err("SSL_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, 22L);
  if(UNEX(res)) {
    err("SSL_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, LO);
  if(UNEX(res)) {
    err("SSL_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, HI);
  if(UNEX(res)) {
    err("SSL_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAIL_AUTH, "string");
  if(UNEX(res)) {
    err("MAIL_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_MAIL_AUTH, NULL);
  if(UNEX(res)) {
    err("MAIL_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SASL_IR, 0L);
  if(UNEX(res)) {
    err("SASL_IR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SASL_IR, 22L);
  if(UNEX(res)) {
    err("SASL_IR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SASL_IR, LO);
  if(UNEX(res)) {
    err("SASL_IR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SASL_IR, HI);
  if(UNEX(res)) {
    err("SASL_IR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION,
                         xferinfocb);
  if(UNEX(res)) {
    err("XFERINFOFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, NULL);
  if(UNEX(res)) {
    err("XFERINFOFUNCTION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, "string");
  if(UNEX(res)) {
    err("XOAUTH2_BEARER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_XOAUTH2_BEARER, NULL);
  if(UNEX(res)) {
    err("XOAUTH2_BEARER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_INTERFACE, "string");
  if(UNEX(res)) {
    err("DNS_INTERFACE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_INTERFACE, NULL);
  if(UNEX(res)) {
    err("DNS_INTERFACE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_LOCAL_IP4, "string");
  if(UNEX(res)) {
    err("DNS_LOCAL_IP4", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_LOCAL_IP4, NULL);
  if(UNEX(res)) {
    err("DNS_LOCAL_IP4", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_LOCAL_IP6, "string");
  if(UNEX(res)) {
    err("DNS_LOCAL_IP6", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DNS_LOCAL_IP6, NULL);
  if(UNEX(res)) {
    err("DNS_LOCAL_IP6", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, "string");
  if(UNEX(res)) {
    err("LOGIN_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, NULL);
  if(UNEX(res)) {
    err("LOGIN_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_NPN, 0L);
  if(UNEX(res)) {
    err("SSL_ENABLE_NPN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_NPN, 22L);
  if(UNEX(res)) {
    err("SSL_ENABLE_NPN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_NPN, LO);
  if(UNEX(res)) {
    err("SSL_ENABLE_NPN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_NPN, HI);
  if(UNEX(res)) {
    err("SSL_ENABLE_NPN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_ALPN, 0L);
  if(UNEX(res)) {
    err("SSL_ENABLE_ALPN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_ALPN, 22L);
  if(UNEX(res)) {
    err("SSL_ENABLE_ALPN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_ALPN, LO);
  if(UNEX(res)) {
    err("SSL_ENABLE_ALPN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_ENABLE_ALPN, HI);
  if(UNEX(res)) {
    err("SSL_ENABLE_ALPN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_EXPECT_100_TIMEOUT_MS, 0L);
  if(UNEX(res)) {
    err("EXPECT_100_TIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_EXPECT_100_TIMEOUT_MS, 22L);
  if(UNEX(res)) {
    err("EXPECT_100_TIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_EXPECT_100_TIMEOUT_MS, LO);
  if(UNEX(res)) {
    err("EXPECT_100_TIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_EXPECT_100_TIMEOUT_MS, HI);
  if(UNEX(res)) {
    err("EXPECT_100_TIMEOUT_MS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYHEADER, slist);
  if(UNEX(res)) {
    err("PROXYHEADER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXYHEADER, NULL);
  if(UNEX(res)) {
    err("PROXYHEADER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADEROPT, 0L);
  if(UNEX(res)) {
    err("HEADEROPT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADEROPT, 22L);
  if(UNEX(res)) {
    err("HEADEROPT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADEROPT, LO);
  if(UNEX(res)) {
    err("HEADEROPT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_HEADEROPT, HI);
  if(UNEX(res)) {
    err("HEADEROPT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, "string");
  if(UNEX(res)) {
    err("PINNEDPUBLICKEY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PINNEDPUBLICKEY, NULL);
  if(UNEX(res)) {
    err("PINNEDPUBLICKEY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, "string");
  if(UNEX(res)) {
    err("UNIX_SOCKET_PATH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, NULL);
  if(UNEX(res)) {
    err("UNIX_SOCKET_PATH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 0L);
  if(UNEX(res)) {
    err("SSL_VERIFYSTATUS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 22L);
  if(UNEX(res)) {
    err("SSL_VERIFYSTATUS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, LO);
  if(UNEX(res)) {
    err("SSL_VERIFYSTATUS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, HI);
  if(UNEX(res)) {
    err("SSL_VERIFYSTATUS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_FALSESTART, 0L);
  if(UNEX(res)) {
    err("SSL_FALSESTART", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_FALSESTART, 22L);
  if(UNEX(res)) {
    err("SSL_FALSESTART", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_FALSESTART, LO);
  if(UNEX(res)) {
    err("SSL_FALSESTART", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SSL_FALSESTART, HI);
  if(UNEX(res)) {
    err("SSL_FALSESTART", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PATH_AS_IS, 0L);
  if(UNEX(res)) {
    err("PATH_AS_IS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PATH_AS_IS, 22L);
  if(UNEX(res)) {
    err("PATH_AS_IS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PATH_AS_IS, LO);
  if(UNEX(res)) {
    err("PATH_AS_IS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PATH_AS_IS, HI);
  if(UNEX(res)) {
    err("PATH_AS_IS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SERVICE_NAME, "string");
  if(UNEX(res)) {
    err("PROXY_SERVICE_NAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SERVICE_NAME, NULL);
  if(UNEX(res)) {
    err("PROXY_SERVICE_NAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SERVICE_NAME, "string");
  if(UNEX(res)) {
    err("SERVICE_NAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SERVICE_NAME, NULL);
  if(UNEX(res)) {
    err("SERVICE_NAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PIPEWAIT, 0L);
  if(UNEX(res)) {
    err("PIPEWAIT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PIPEWAIT, 22L);
  if(UNEX(res)) {
    err("PIPEWAIT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PIPEWAIT, LO);
  if(UNEX(res)) {
    err("PIPEWAIT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PIPEWAIT, HI);
  if(UNEX(res)) {
    err("PIPEWAIT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "string");
  if(UNEX(res)) {
    err("DEFAULT_PROTOCOL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, NULL);
  if(UNEX(res)) {
    err("DEFAULT_PROTOCOL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STREAM_WEIGHT, 0L);
  if(UNEX(res)) {
    err("STREAM_WEIGHT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STREAM_WEIGHT, 22L);
  if(UNEX(res)) {
    err("STREAM_WEIGHT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STREAM_WEIGHT, LO);
  if(UNEX(res)) {
    err("STREAM_WEIGHT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STREAM_WEIGHT, HI);
  if(UNEX(res)) {
    err("STREAM_WEIGHT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STREAM_DEPENDS, dep);
  if(UNEX(res)) {
    err("STREAM_DEPENDS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STREAM_DEPENDS, NULL);
  if(UNEX(res)) {
    err("STREAM_DEPENDS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STREAM_DEPENDS_E, dep);
  if(UNEX(res)) {
    err("STREAM_DEPENDS_E", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_STREAM_DEPENDS_E, NULL);
  if(UNEX(res)) {
    err("STREAM_DEPENDS_E", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TFTP_NO_OPTIONS, 0L);
  if(UNEX(res)) {
    err("TFTP_NO_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TFTP_NO_OPTIONS, 22L);
  if(UNEX(res)) {
    err("TFTP_NO_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TFTP_NO_OPTIONS, LO);
  if(UNEX(res)) {
    err("TFTP_NO_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TFTP_NO_OPTIONS, HI);
  if(UNEX(res)) {
    err("TFTP_NO_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECT_TO, &object);
  if(UNEX(res)) {
    err("CONNECT_TO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_CONNECT_TO, NULL);
  if(UNEX(res)) {
    err("CONNECT_TO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_FASTOPEN, 0L);
  if(UNEX(res)) {
    err("TCP_FASTOPEN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_FASTOPEN, 22L);
  if(UNEX(res)) {
    err("TCP_FASTOPEN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_FASTOPEN, LO);
  if(UNEX(res)) {
    err("TCP_FASTOPEN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_TCP_FASTOPEN, HI);
  if(UNEX(res)) {
    err("TCP_FASTOPEN", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_KEEP_SENDING_ON_ERROR, 0L);
  if(UNEX(res)) {
    err("KEEP_SENDING_ON_ERROR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_KEEP_SENDING_ON_ERROR, 22L);
  if(UNEX(res)) {
    err("KEEP_SENDING_ON_ERROR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_KEEP_SENDING_ON_ERROR, LO);
  if(UNEX(res)) {
    err("KEEP_SENDING_ON_ERROR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_KEEP_SENDING_ON_ERROR, HI);
  if(UNEX(res)) {
    err("KEEP_SENDING_ON_ERROR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_CAINFO, "string");
  if(UNEX(res)) {
    err("PROXY_CAINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_CAINFO, NULL);
  if(UNEX(res)) {
    err("PROXY_CAINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_CAPATH, "string");
  if(UNEX(res)) {
    err("PROXY_CAPATH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_CAPATH, NULL);
  if(UNEX(res)) {
    err("PROXY_CAPATH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYPEER, 0L);
  if(UNEX(res)) {
    err("PROXY_SSL_VERIFYPEER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYPEER, 22L);
  if(UNEX(res)) {
    err("PROXY_SSL_VERIFYPEER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYPEER, LO);
  if(UNEX(res)) {
    err("PROXY_SSL_VERIFYPEER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYPEER, HI);
  if(UNEX(res)) {
    err("PROXY_SSL_VERIFYPEER", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYHOST, 0L);
  if(UNEX(res)) {
    err("PROXY_SSL_VERIFYHOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYHOST, 22L);
  if(UNEX(res)) {
    err("PROXY_SSL_VERIFYHOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYHOST, LO);
  if(UNEX(res)) {
    err("PROXY_SSL_VERIFYHOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_VERIFYHOST, HI);
  if(UNEX(res)) {
    err("PROXY_SSL_VERIFYHOST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLVERSION, 0L);
  if(UNEX(res)) {
    err("PROXY_SSLVERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLVERSION, 22L);
  if(UNEX(res)) {
    err("PROXY_SSLVERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLVERSION, LO);
  if(UNEX(res)) {
    err("PROXY_SSLVERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLVERSION, HI);
  if(UNEX(res)) {
    err("PROXY_SSLVERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TLSAUTH_USERNAME, "string");
  if(UNEX(res)) {
    err("PROXY_TLSAUTH_USERNAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TLSAUTH_USERNAME, NULL);
  if(UNEX(res)) {
    err("PROXY_TLSAUTH_USERNAME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TLSAUTH_PASSWORD, "string");
  if(UNEX(res)) {
    err("PROXY_TLSAUTH_PASSWORD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TLSAUTH_PASSWORD, NULL);
  if(UNEX(res)) {
    err("PROXY_TLSAUTH_PASSWORD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TLSAUTH_TYPE, "string");
  if(UNEX(res)) {
    err("PROXY_TLSAUTH_TYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_TLSAUTH_TYPE, NULL);
  if(UNEX(res)) {
    err("PROXY_TLSAUTH_TYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLCERT, "string");
  if(UNEX(res)) {
    err("PROXY_SSLCERT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLCERT, NULL);
  if(UNEX(res)) {
    err("PROXY_SSLCERT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLCERTTYPE, "string");
  if(UNEX(res)) {
    err("PROXY_SSLCERTTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLCERTTYPE, NULL);
  if(UNEX(res)) {
    err("PROXY_SSLCERTTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLKEY, "string");
  if(UNEX(res)) {
    err("PROXY_SSLKEY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLKEY, NULL);
  if(UNEX(res)) {
    err("PROXY_SSLKEY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLKEYTYPE, "string");
  if(UNEX(res)) {
    err("PROXY_SSLKEYTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSLKEYTYPE, NULL);
  if(UNEX(res)) {
    err("PROXY_SSLKEYTYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_KEYPASSWD, "string");
  if(UNEX(res)) {
    err("PROXY_KEYPASSWD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_KEYPASSWD, NULL);
  if(UNEX(res)) {
    err("PROXY_KEYPASSWD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_CIPHER_LIST, "string");
  if(UNEX(res)) {
    err("PROXY_SSL_CIPHER_LIST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_CIPHER_LIST, NULL);
  if(UNEX(res)) {
    err("PROXY_SSL_CIPHER_LIST", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_CRLFILE, "string");
  if(UNEX(res)) {
    err("PROXY_CRLFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_CRLFILE, NULL);
  if(UNEX(res)) {
    err("PROXY_CRLFILE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_OPTIONS, 0L);
  if(UNEX(res)) {
    err("PROXY_SSL_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_OPTIONS, 22L);
  if(UNEX(res)) {
    err("PROXY_SSL_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_OPTIONS, LO);
  if(UNEX(res)) {
    err("PROXY_SSL_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_SSL_OPTIONS, HI);
  if(UNEX(res)) {
    err("PROXY_SSL_OPTIONS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PRE_PROXY, "string");
  if(UNEX(res)) {
    err("PRE_PROXY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PRE_PROXY, NULL);
  if(UNEX(res)) {
    err("PRE_PROXY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_PINNEDPUBLICKEY, "string");
  if(UNEX(res)) {
    err("PROXY_PINNEDPUBLICKEY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_PROXY_PINNEDPUBLICKEY, NULL);
  if(UNEX(res)) {
    err("PROXY_PINNEDPUBLICKEY", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ABSTRACT_UNIX_SOCKET, "string");
  if(UNEX(res)) {
    err("ABSTRACT_UNIX_SOCKET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_ABSTRACT_UNIX_SOCKET, NULL);
  if(UNEX(res)) {
    err("ABSTRACT_UNIX_SOCKET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SUPPRESS_CONNECT_HEADERS, 0L);
  if(UNEX(res)) {
    err("SUPPRESS_CONNECT_HEADERS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SUPPRESS_CONNECT_HEADERS, 22L);
  if(UNEX(res)) {
    err("SUPPRESS_CONNECT_HEADERS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SUPPRESS_CONNECT_HEADERS, LO);
  if(UNEX(res)) {
    err("SUPPRESS_CONNECT_HEADERS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SUPPRESS_CONNECT_HEADERS, HI);
  if(UNEX(res)) {
    err("SUPPRESS_CONNECT_HEADERS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_REQUEST_TARGET, "string");
  if(UNEX(res)) {
    err("REQUEST_TARGET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_REQUEST_TARGET, NULL);
  if(UNEX(res)) {
    err("REQUEST_TARGET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_AUTH, 0L);
  if(UNEX(res)) {
    err("SOCKS5_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_AUTH, 22L);
  if(UNEX(res)) {
    err("SOCKS5_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_AUTH, LO);
  if(UNEX(res)) {
    err("SOCKS5_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_setopt(curl, CURLOPT_SOCKS5_AUTH, HI);
  if(UNEX(res)) {
    err("SOCKS5_AUTH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &charp);
  if(UNEX(res)) {
    geterr("EFFECTIVE_URL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &val);
  if(UNEX(res)) {
    geterr("RESPONSE_CODE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &dval);
  if(UNEX(res)) {
    geterr("TOTAL_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &dval);
  if(UNEX(res)) {
    geterr("NAMELOOKUP_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &dval);
  if(UNEX(res)) {
    geterr("CONNECT_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_PRETRANSFER_TIME, &dval);
  if(UNEX(res)) {
    geterr("PRETRANSFER_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SIZE_UPLOAD, &dval);
  if(UNEX(res)) {
    geterr("SIZE_UPLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SIZE_UPLOAD_T, &oval);
  if(UNEX(res)) {
    geterr("SIZE_UPLOAD_T", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD, &dval);
  if(UNEX(res)) {
    geterr("SIZE_DOWNLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SIZE_DOWNLOAD_T, &oval);
  if(UNEX(res)) {
    geterr("SIZE_DOWNLOAD_T", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &dval);
  if(UNEX(res)) {
    geterr("SPEED_DOWNLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD_T, &oval);
  if(UNEX(res)) {
    geterr("SPEED_DOWNLOAD_T", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &dval);
  if(UNEX(res)) {
    geterr("SPEED_UPLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD_T, &oval);
  if(UNEX(res)) {
    geterr("SPEED_UPLOAD_T", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_HEADER_SIZE, &val);
  if(UNEX(res)) {
    geterr("HEADER_SIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_REQUEST_SIZE, &val);
  if(UNEX(res)) {
    geterr("REQUEST_SIZE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SSL_VERIFYRESULT, &val);
  if(UNEX(res)) {
    geterr("SSL_VERIFYRESULT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_FILETIME, &val);
  if(UNEX(res)) {
    geterr("FILETIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &dval);
  if(UNEX(res)) {
    geterr("CONTENT_LENGTH_DOWNLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &oval);
  if(UNEX(res)) {
    geterr("CONTENT_LENGTH_DOWNLOAD_T", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_UPLOAD, &dval);
  if(UNEX(res)) {
    geterr("CONTENT_LENGTH_UPLOAD", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_UPLOAD_T, &oval);
  if(UNEX(res)) {
    geterr("CONTENT_LENGTH_UPLOAD_T", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_STARTTRANSFER_TIME, &dval);
  if(UNEX(res)) {
    geterr("STARTTRANSFER_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &charp);
  if(UNEX(res)) {
    geterr("CONTENT_TYPE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_TIME, &dval);
  if(UNEX(res)) {
    geterr("REDIRECT_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_COUNT, &val);
  if(UNEX(res)) {
    geterr("REDIRECT_COUNT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_PRIVATE, &charp);
  if(UNEX(res)) {
    geterr("PRIVATE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_HTTP_CONNECTCODE, &val);
  if(UNEX(res)) {
    geterr("HTTP_CONNECTCODE", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_HTTPAUTH_AVAIL, &val);
  if(UNEX(res)) {
    geterr("HTTPAUTH_AVAIL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_PROXYAUTH_AVAIL, &val);
  if(UNEX(res)) {
    geterr("PROXYAUTH_AVAIL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_OS_ERRNO, &val);
  if(UNEX(res)) {
    geterr("OS_ERRNO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_NUM_CONNECTS, &val);
  if(UNEX(res)) {
    geterr("NUM_CONNECTS", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SSL_ENGINES, &slist);
  if(UNEX(res)) {
    geterr("SSL_ENGINES", res, __LINE__); goto test_cleanup; }
  if(slist)
    curl_slist_free_all(slist);
  res = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &slist);
  if(UNEX(res)) {
    geterr("COOKIELIST", res, __LINE__); goto test_cleanup; }
  if(slist)
    curl_slist_free_all(slist);
  res = curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &val);
  if(UNEX(res)) {
    geterr("LASTSOCKET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_FTP_ENTRY_PATH, &charp);
  if(UNEX(res)) {
    geterr("FTP_ENTRY_PATH", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &charp);
  if(UNEX(res)) {
    geterr("REDIRECT_URL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &charp);
  if(UNEX(res)) {
    geterr("PRIMARY_IP", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_APPCONNECT_TIME, &dval);
  if(UNEX(res)) {
    geterr("APPCONNECT_TIME", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_CERTINFO, &certinfo);
  if(UNEX(res)) {
    geterr("CERTINFO", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_CONDITION_UNMET, &val);
  if(UNEX(res)) {
    geterr("CONDITION_UNMET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_RTSP_SESSION_ID, &charp);
  if(UNEX(res)) {
    geterr("RTSP_SESSION_ID", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_RTSP_CLIENT_CSEQ, &val);
  if(UNEX(res)) {
    geterr("RTSP_CLIENT_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_RTSP_SERVER_CSEQ, &val);
  if(UNEX(res)) {
    geterr("RTSP_SERVER_CSEQ", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_RTSP_CSEQ_RECV, &val);
  if(UNEX(res)) {
    geterr("RTSP_CSEQ_RECV", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_PRIMARY_PORT, &val);
  if(UNEX(res)) {
    geterr("PRIMARY_PORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_LOCAL_IP, &charp);
  if(UNEX(res)) {
    geterr("LOCAL_IP", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_LOCAL_PORT, &val);
  if(UNEX(res)) {
    geterr("LOCAL_PORT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_TLS_SESSION, &tlssession);
  if(UNEX(res)) {
    geterr("TLS_SESSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_ACTIVESOCKET, &sockfd);
  if(UNEX(res)) {
    geterr("ACTIVESOCKET", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_TLS_SSL_PTR, &tlssession);
  if(UNEX(res)) {
    geterr("TLS_SSL_PTR", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_HTTP_VERSION, &val);
  if(UNEX(res)) {
    geterr("HTTP_VERSION", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_PROXY_SSL_VERIFYRESULT, &val);
  if(UNEX(res)) {
    geterr("PROXY_SSL_VERIFYRESULT", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_PROTOCOL, &val);
  if(UNEX(res)) {
    geterr("PROTOCOL", res, __LINE__); goto test_cleanup; }
  res = curl_easy_getinfo(curl, CURLINFO_SCHEME, &charp);
  if(UNEX(res)) {
    geterr("SCHEME", res, __LINE__); goto test_cleanup; }
  curl_easy_setopt(curl, 1, 0);
  res = CURLE_OK;
test_cleanup:
  curl_easy_cleanup(curl);
  curl_easy_cleanup(dep);
  curl_share_cleanup(share);

  return (int)res;
}