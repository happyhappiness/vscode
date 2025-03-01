static int err(const char *name, CURLcode val, int lineno)
{
  printf("CURLOPT_%s returned %d, \"%s\" on line %d\n",
         name, val, curl_easy_strerror(val), lineno);
  return (int)val;
}