static void
cleanup_quote (struct q_class_t **QuoteList)
{
  struct q_class_t *ptr;

  while (*QuoteList)
  {
    if ((*QuoteList)->down)
      cleanup_quote (&((*QuoteList)->down));
    ptr = (*QuoteList)->next;
    if ((*QuoteList)->prefix)
      safe_free ((void **) &(*QuoteList)->prefix);
    safe_free ((void **) QuoteList);
    *QuoteList = ptr;
  }

  return;
}