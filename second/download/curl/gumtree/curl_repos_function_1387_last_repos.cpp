static void conn_llist_dtor(void *user, void *element)
{
  struct connectdata *data = element;
  (void)user;

  data->bundle = NULL;
}