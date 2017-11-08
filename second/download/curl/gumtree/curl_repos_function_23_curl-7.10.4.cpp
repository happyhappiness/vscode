URL_FILE *url_fopen(char *url, char *operation)
{
  /* this code could check for URLs or types in the 'url' and
     basicly use the real fopen() for standard files */

  URL_FILE *file;
  int still_running;
  (void)operation;

  file = (URL_FILE *)malloc(sizeof(URL_FILE));
  if(!file)
    return NULL;

  memset(file, 0, sizeof(URL_FILE));

  file->type = 1; /* marked as URL, use 0 for plain file */
  file->handle.curl = curl_easy_init();

  curl_easy_setopt(file->handle.curl, CURLOPT_URL, url);
  curl_easy_setopt(file->handle.curl, CURLOPT_FILE, file);
  curl_easy_setopt(file->handle.curl, CURLOPT_VERBOSE, FALSE);
  curl_easy_setopt(file->handle.curl, CURLOPT_WRITEFUNCTION, write_callback);

  if(!multi_handle)
    multi_handle = curl_multi_init();

  curl_multi_add_handle(multi_handle, file->handle.curl);

  while(CURLM_CALL_MULTI_PERFORM ==
        curl_multi_perform(multi_handle, &still_running));

  /* if still_running would be 0 now, we should return NULL */

  return file;
}