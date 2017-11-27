int udb_query_prepare_result (udb_query_t *q, /* {{{ */
    const char *host, const char *plugin, const char *db_name,
    char **column_names, size_t column_num)
{
  udb_result_t *r;
  int status;

  if (q == NULL)
    return (-EINVAL);

  udb_query_finish_result (q);

  q->column_num = column_num;
  q->host = strdup (host);
  q->plugin = strdup (plugin);
  q->db_name = strdup (db_name);

  if ((q->host == NULL) || (q->plugin == NULL) || (q->db_name == NULL))
  {
    ERROR ("db query utils: Query `%s': Prepare failed: Out of memory.", q->name);
    udb_query_finish_result (q);
    return (-ENOMEM);
  }

#if defined(COLLECT_DEBUG) && COLLECT_DEBUG
  do
  {
    size_t i;

    for (i = 0; i < column_num; i++)
    {
      DEBUG ("db query utils: udb_query_prepare_result: "
          "query = %s; column[%zu] = %s;",
          q->name, i, column_names[i]);
    }
  } while (0);
#endif

  for (r = q->results; r != NULL; r = r->next)
  {
    status = udb_result_prepare_result (r, column_names, column_num);
    if (status != 0)
    {
      udb_query_finish_result (q);
      return (status);
    }
  }

  return (0);
}