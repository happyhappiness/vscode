const char *udb_query_get_name(udb_query_t *q) /* {{{ */
{
  if (q == NULL)
    return NULL;

  return q->name;
}