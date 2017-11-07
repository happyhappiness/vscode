void mutt_free_parameter (PARAMETER **p)
{
  PARAMETER *t = *p;
  PARAMETER *o;

  while (t)
  {
    safe_free ((void **) &t->attribute);
    safe_free ((void **) &t->value);
    o = t;
    t = t->next;
    safe_free ((void **) &o);
  }
  *p = 0;
}