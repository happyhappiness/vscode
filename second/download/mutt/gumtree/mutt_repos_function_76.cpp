LIST *mutt_copy_list (LIST *p)
{
  LIST *t, *r=NULL, *l=NULL;

  for (; p; p = p->next)
  {
    t = (LIST *) safe_malloc (sizeof (LIST));
    t->data = safe_strdup (p->data);
    t->next = NULL;
    if (l)
    {
      r->next = t;
      r = r->next;
    }
    else
      l = r = t;
  }
  return (l);
}