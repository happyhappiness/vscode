static void free_query (QUERY **query)
{
  QUERY *p;

  if (!query)
    return;

  while (*query)
  {
    p = *query;
    *query = (*query)->next;

    rfc822_free_address (&p->addr);
    FREE (&p->name);
    FREE (&p->other);
    FREE (&p);
  }
}