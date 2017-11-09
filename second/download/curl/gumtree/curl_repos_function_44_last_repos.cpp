int main(int argc, char **argv)
{
  int rc = CURLE_OK;

  /* curl easy handle */
  CURL *handle;

  /* help data */
  struct callback_data data = { 0 };

  /* global initialization */
  rc = curl_global_init(CURL_GLOBAL_ALL);
  if(rc)
    return rc;

  /* initialization of easy handle */
  handle = curl_easy_init();
  if(!handle) {
    curl_global_cleanup();
    return CURLE_OUT_OF_MEMORY;
  }

  /* turn on wildcard matching */
  curl_easy_setopt(handle, CURLOPT_WILDCARDMATCH, 1L);

  /* callback is called before download of concrete file started */
  curl_easy_setopt(handle, CURLOPT_CHUNK_BGN_FUNCTION, file_is_coming);

  /* callback is called after data from the file have been transferred */
  curl_easy_setopt(handle, CURLOPT_CHUNK_END_FUNCTION, file_is_downloaded);

  /* this callback will write contents into files */
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_it);

  /* put transfer data into callbacks */
  curl_easy_setopt(handle, CURLOPT_CHUNK_DATA, &data);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &data);

  /* curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L); */

  /* set an URL containing wildcard pattern (only in the last part) */
  if(argc == 2)
    curl_easy_setopt(handle, CURLOPT_URL, argv[1]);
  else
    curl_easy_setopt(handle, CURLOPT_URL, "ftp://example.com/test/*");

  /* and start transfer! */
  rc = curl_easy_perform(handle);

  curl_easy_cleanup(handle);
  curl_global_cleanup();
  return rc;
}