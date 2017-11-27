static int powerdns_shutdown (void)
{
  llentry_t *e;

  if (list == NULL)
    return (0);

  for (e = llist_head (list); e != NULL; e = e->next)
  {
    list_item_t *item = (list_item_t *) e->value;
    e->value = NULL;

    sfree (item->instance);
    sfree (item->command);
    sfree (item);
  }

  llist_destroy (list);
  list = NULL;

  return (0);
}