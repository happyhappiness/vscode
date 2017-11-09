void mutt_free_parameter (PARAMETER **p)
{
  PARAMETER *t = *p;
  PARAMETER *o;

  while (t)
  {
    FREE (&t->attribute);
    FREE (&t->value);
    o = t;
    t = t->next;
    FREE (&o);
  }
  *p = 0;
}