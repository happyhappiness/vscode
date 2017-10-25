CURL *curl_easy_init(void)
{
  CURLcode res;
  struct UrlData *data;

  if(curl_init())
    return NULL;

  /* We use curl_open() with undefined URL so far */
  res = curl_open((CURL **)&data, NULL);
  if(res != CURLE_OK)
    return NULL;

  data->interf = CURLI_EASY; /* mark it as an easy one */
  return data;
}