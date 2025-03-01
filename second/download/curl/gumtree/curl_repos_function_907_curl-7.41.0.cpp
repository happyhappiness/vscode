char *curl_easy_unescape(CURL *handle, const char *string, int length,
                         int *olen)
{
  char *str = NULL;
  size_t inputlen = length;
  size_t outputlen;
  CURLcode res = Curl_urldecode(handle, string, inputlen, &str, &outputlen,
                                FALSE);
  if(res)
    return NULL;
  if(olen)
    *olen = curlx_uztosi(outputlen);
  return str;
}