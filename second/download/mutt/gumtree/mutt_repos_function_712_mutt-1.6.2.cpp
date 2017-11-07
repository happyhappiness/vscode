static int crypt_compare_address (const void *a, const void *b)
{
  return ((PgpSortKeys & SORT_REVERSE) ? !_crypt_compare_address (a, b)
                                         :  _crypt_compare_address (a, b));
}