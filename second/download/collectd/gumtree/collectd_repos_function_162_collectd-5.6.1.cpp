static int cdbi_shutdown (void) /* {{{ */
{
  for (size_t i = 0; i < databases_num; i++)
  {
    if (databases[i]->connection != NULL)
    {
      dbi_conn_close (databases[i]->connection);
      databases[i]->connection = NULL;
    }
    cdbi_database_free (databases[i]);
  }
  sfree (databases);
  databases_num = 0;

  udb_query_free (queries, queries_num);
  queries = NULL;
  queries_num = 0;

  return (0);
}