void udb_query_finish_result (udb_query_t *q) /* {{{ */
{
  udb_result_t *r;

  if (q == NULL)
    return;

  q->column_num = 0;
  sfree (q->host);
  sfree (q->plugin);
  sfree (q->db_name);

  for (r = q->results; r != NULL; r = r->next)
    udb_result_finish_result (r);
}