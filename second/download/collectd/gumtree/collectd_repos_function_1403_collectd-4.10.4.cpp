void udb_query_free_one (udb_query_t *q) /* {{{ */
{
  if (q == NULL)
    return;

  sfree (q->name);
  sfree (q->statement);

  udb_result_free (q->results);

  sfree (q);
}