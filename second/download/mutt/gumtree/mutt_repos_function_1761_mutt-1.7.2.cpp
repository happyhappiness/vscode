static int pgp_compare_address (const void *a, const void *b)
{
  return ((PgpSortKeys & SORT_REVERSE) ? !_pgp_compare_address (a, b)
				       : _pgp_compare_address (a, b));
}