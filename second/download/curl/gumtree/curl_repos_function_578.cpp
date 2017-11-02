static CURLcode unit_setup(void)
{
  llist = Curl_llist_alloc(test_curl_llist_dtor);
  if(!llist)
    return CURLE_OUT_OF_MEMORY;
  llist_destination = Curl_llist_alloc(test_curl_llist_dtor);
  if(!llist_destination) {
      Curl_llist_destroy(llist, NULL);
      return CURLE_OUT_OF_MEMORY;
  }

  return CURLE_OK;
}