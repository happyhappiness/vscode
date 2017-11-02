static void unit_stop(void)
{
  Curl_llist_destroy(llist, NULL);
  Curl_llist_destroy(llist_destination, NULL);
}