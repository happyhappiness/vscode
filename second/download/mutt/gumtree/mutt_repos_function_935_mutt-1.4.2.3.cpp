void mutt_free_alias (ALIAS **p)
{
  ALIAS *t;

  while (*p)
  {
    t = *p;
    *p = (*p)->next;
    safe_free ((void **) &t->name);
    rfc822_free_address (&t->addr);
    safe_free ((void **) &t);
  }
}