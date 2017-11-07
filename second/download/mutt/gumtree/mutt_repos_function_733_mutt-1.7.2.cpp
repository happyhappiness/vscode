static int crypt_compare_keyid (const void *a, const void *b)
{
  return ((PgpSortKeys & SORT_REVERSE) ? !_crypt_compare_keyid (a, b)
		                         :  _crypt_compare_keyid (a, b));
}