static int powerdns_shutdown (void)
{
  if (list == NULL)
    return (0);

  for (llentry_t *e = llist_head (list); e != NULL; e = e->next)
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