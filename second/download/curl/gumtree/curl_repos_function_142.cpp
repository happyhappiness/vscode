int glob_url(URLGlob** glob, char* url, int *urlnum, FILE *error)
{
  /*
   * We can deal with any-size, just make a buffer with the same length
   * as the specified URL!
   */
  URLGlob *glob_expand;
  int amount;
  char *glob_buffer=(char *)malloc(strlen(url)+1);

  *glob = NULL;
  if(NULL == glob_buffer)
    return CURLE_OUT_OF_MEMORY;

  glob_expand = (URLGlob*)calloc(sizeof(URLGlob), 1);
  if(NULL == glob_expand) {
    free(glob_buffer);
    return CURLE_OUT_OF_MEMORY;
  }
  glob_expand->size = 0;
  glob_expand->urllen = strlen(url);
  glob_expand->glob_buffer = glob_buffer;
  glob_expand->beenhere=0;
  if(GLOB_OK == glob_word(glob_expand, url, 1, &amount))
    *urlnum = amount;
  else {
    if(error && glob_expand->errormsg[0]) {
      /* send error description to the error-stream */
      fprintf(error, "curl: (%d) [globbing] %s\n",
              CURLE_URL_MALFORMAT, glob_expand->errormsg);
    }
    /* it failed, we cleanup */
    free(glob_buffer);
    free(glob_expand);
    glob_expand = NULL;
    *urlnum = 1;
    return CURLE_URL_MALFORMAT;
  }

  *glob = glob_expand;
  return CURLE_OK;
}