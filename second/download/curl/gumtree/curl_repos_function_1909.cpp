static void server_blacklist_llist_dtor(void *user, void *element)
{
  char *server_name = element;
  (void)user;

  Curl_safefree(server_name);
}