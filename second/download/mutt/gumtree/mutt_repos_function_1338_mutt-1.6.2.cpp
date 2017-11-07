LIST *mutt_find_list (LIST *l, const char *data)
{
  LIST *p = l;

  while (p)
  {
    if (data == p->data)
      return p;
    if (data && p->data && mutt_strcmp (p->data, data) == 0)
      return p;
    p = p->next;
  }
  return NULL;
}