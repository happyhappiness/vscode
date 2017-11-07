static int crypt_compare_date (const void *a, const void *b)
{
  return ((PgpSortKeys & SORT_REVERSE) ? !_crypt_compare_date (a, b)
                                         :  _crypt_compare_date (a, b));
}