void udb_query_free(udb_query_t **query_list, size_t query_list_len) /* {{{ */
{
  if (query_list == NULL)
    return;

  for (size_t i = 0; i < query_list_len; i++)
    udb_query_free_one(query_list[i]);

  sfree(query_list);
}