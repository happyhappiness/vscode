int ut_search_threshold (const value_list_t *vl, /* {{{ */
    threshold_t *ret_threshold)
{
  threshold_t *t;

  if (vl == NULL)
    return (EINVAL);

  t = threshold_search (vl);
  if (t == NULL)
    return (ENOENT);

  memcpy (ret_threshold, t, sizeof (*ret_threshold));
  ret_threshold->next = NULL;

  return (0);
}