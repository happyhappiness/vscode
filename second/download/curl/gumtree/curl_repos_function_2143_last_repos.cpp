static void server_blacklist_llist_dtor(void *user, void *element)
{
  (void)user;
  free(element);
}