void udb_query_set_user_data(udb_query_t *q, void *user_data) /* {{{ */
{
  if (q == NULL)
    return;

  q->user_data = user_data;
}