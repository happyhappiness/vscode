int glob_url(URLGlob** glob, char* url, int *urlnum)
{
  if (strlen(url)>URL_MAX_LENGTH) {
    printf("Illegally sized URL\n");
    return CURLE_URL_MALFORMAT;
  }

  glob_expand = (URLGlob*)malloc(sizeof(URLGlob));
  glob_expand->size = 0;
  *urlnum = glob_word(url, 1);
  *glob = glob_expand;
  return CURLE_OK;
}