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
      FREE (&(*QuoteList)->prefix);
    FREE (QuoteList);		/* __FREE_CHECKED__ */
    *QuoteList = ptr;
  }

  return;
}