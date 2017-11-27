void *udb_query_get_user_data(udb_query_t *q) /* {{{ */
{
  if (q == NULL)
    return (NULL);

  return (q->user_data);
}