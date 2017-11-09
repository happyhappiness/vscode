static struct curl_slist *sethost(struct curl_slist *headers)
{
  (void)headers;
  return curl_slist_append(NULL, HOSTHEADER);
}