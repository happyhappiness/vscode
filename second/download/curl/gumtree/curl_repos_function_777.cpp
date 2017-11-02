static char *my_useragent(void)
{
  return strdup(CURL_NAME "/" CURL_VERSION);
}