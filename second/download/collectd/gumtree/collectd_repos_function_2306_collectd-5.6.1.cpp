int lcc_sort_identifiers (lcc_connection_t *c, /* {{{ */
    lcc_identifier_t *idents, size_t idents_num)
{
  if (idents == NULL)
  {
    lcc_set_errno (c, EINVAL);
    return (-1);
  }

  qsort (idents, idents_num, sizeof (*idents),
      lcc_identifier_compare);
  return (0);
}