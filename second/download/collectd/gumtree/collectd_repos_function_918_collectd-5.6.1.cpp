static int powerdns_read (void)
{
  for (llentry_t *e = llist_head (list); e != NULL; e = e->next)
  {
    list_item_t *item = e->value;
    item->func (item);
  }

  return (0);
}