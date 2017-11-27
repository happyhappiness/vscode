const char *udb_query_get_statement(udb_query_t *q) /* {{{ */
{
  if (q == NULL)
    return (NULL);

  return (q->statement);
}