static void *fire(void *ptr)
{
  CURLcode code;
  struct curl_slist *headers;
  struct Tdata *tdata = (struct Tdata*)ptr;
  CURL *curl;
  int i=0;

  if ((curl = curl_easy_init()) == NULL) {
    fprintf(stderr, "curl_easy_init() failed\n");
    return NULL;
  }

  headers = sethost(NULL);
  curl_easy_setopt(curl, CURLOPT_VERBOSE,    1L);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(curl, CURLOPT_URL,        tdata->url);
  printf( "CURLOPT_SHARE\n" );
  curl_easy_setopt(curl, CURLOPT_SHARE, tdata->share);

  printf( "PERFORM\n" );
  code = curl_easy_perform(curl);
  if( code != CURLE_OK ) {
    fprintf(stderr, "perform url '%s' repeat %d failed, curlcode %d\n",
            tdata->url, i, (int)code);
  }

  printf( "CLEANUP\n" );
  curl_easy_cleanup(curl);
  curl_slist_free_all(headers);

  return NULL;
}