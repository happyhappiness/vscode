static void udb_query_free_one(udb_query_t *q) /* {{{ */
{
  if (q == NULL)
    return;

  sfree(q->name);
  sfree(q->statement);
  sfree(q->plugin_instance_from);

  udb_result_free(q->results);

  sfree(q);
}