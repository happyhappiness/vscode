static void site_blacklist_llist_dtor(void *user, void *element)
{
  struct site_blacklist_entry *entry = element;
  (void)user;

  Curl_safefree(entry->hostname);
  free(entry);
}