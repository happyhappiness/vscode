static int powerdns_read (void)
{
  llentry_t *e;

  for (e = llist_head (list); e != NULL; e = e->next)
  {
    list_item_t *item = e->value;
    item->func (item);
  }

  return (0);
}