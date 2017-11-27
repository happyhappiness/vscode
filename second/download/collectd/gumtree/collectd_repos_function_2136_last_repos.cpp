int udb_query_check_version(udb_query_t *q, unsigned int version) /* {{{ */
{
  if (q == NULL)
    return -EINVAL;

  if ((version < q->min_version) || (version > q->max_version))
    return 0;

  return 1;
}