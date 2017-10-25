void *fire(void *ptr)
{
  CURLcode code;
  struct curl_slist *headers;
  struct Tdata *tdata = (struct Tdata*)ptr;
  CURL *curl = curl_easy_init();
  int i=0;

  headers = sethost(NULL);
  curl_easy_setopt(curl, CURLOPT_VERBOSE,    1);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, (void*)headers);
  curl_easy_setopt(curl, CURLOPT_URL,        (void*)tdata->url);
  printf( "CURLOPT_SHARE\n" );
  curl_easy_setopt(curl, CURLOPT_SHARE, (void*)tdata->share);

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