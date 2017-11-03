static int pgp_compare_keyid (const void *a, const void *b)
{
  return ((PgpSortKeys & SORT_REVERSE) ? !_pgp_compare_keyid (a, b)
				       : _pgp_compare_keyid (a, b));
}