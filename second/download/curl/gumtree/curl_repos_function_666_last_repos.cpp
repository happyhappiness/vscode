static CURLcode unit_setup(void)
{
  Curl_llist_init(&llist, test_curl_llist_dtor);
  Curl_llist_init(&llist_destination, test_curl_llist_dtor);
  return CURLE_OK;
}