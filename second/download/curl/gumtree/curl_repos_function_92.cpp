CURLcode curl_close(CURL *curl)
{
  struct UrlData *data=(struct UrlData *)curl;
  
  void *protocol = data->proto.generic;

  /* total session cleanup (frees 'data' as well!)*/
  urlfree(data, TRUE);

  if(protocol)
    free(protocol);

  return CURLE_OK;
}