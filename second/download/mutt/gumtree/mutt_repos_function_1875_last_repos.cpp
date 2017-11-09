static int pgp_compare_trust (const void *a, const void *b)
{
  return ((PgpSortKeys & SORT_REVERSE) ? !_pgp_compare_trust (a, b)
				       : _pgp_compare_trust (a, b));
}