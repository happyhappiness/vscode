static int pgp_compare_date (const void *a, const void *b)
{
  return ((PgpSortKeys & SORT_REVERSE) ? !_pgp_compare_date (a, b)
				       : _pgp_compare_date (a, b));
}