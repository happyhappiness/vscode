int udb_query_handle_result (udb_query_t *q, char **column_values) /* {{{ */
{
  udb_result_t *r;
  int success;
  int status;

  if (q == NULL)
    return (-EINVAL);

  if ((q->column_num < 1) || (q->host == NULL) || (q->plugin == NULL)
      || (q->db_name == NULL))
  {
    ERROR ("db query utils: Query `%s': Query is not prepared; "
        "can't handle result.", q->name);
    return (-EINVAL);
  }

#if defined(COLLECT_DEBUG) && COLLECT_DEBUG /* {{{ */
  do
  {
    size_t i;

    for (i = 0; i < q->column_num; i++)
    {
      DEBUG ("db query utils: udb_query_handle_result (%s, %s): "
          "column[%zu] = %s;",
          q->db_name, q->name, i, column_values[i]);
    }
  } while (0);
#endif /* }}} */

  success = 0;
  for (r = q->results; r != NULL; r = r->next)
  {
    status = udb_result_handle_result (r, q, column_values);
    if (status == 0)
      success++;
  }

  if (success == 0)
  {
    ERROR ("db query utils: udb_query_handle_result (%s, %s): "
        "All results failed.", q->db_name, q->name);
    return (-1);
  }

  return (0);
}