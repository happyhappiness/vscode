static int crypt_compare_trust (const void *a, const void *b)
{
  return ((PgpSortKeys & SORT_REVERSE) ? !_crypt_compare_trust (a, b)
  				       : _crypt_compare_trust (a, b));
}