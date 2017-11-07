static int _crypt_compare_address (const void *a, const void *b)
{
  crypt_key_t **s = (crypt_key_t **) a;
  crypt_key_t **t = (crypt_key_t **) b;
  int r;

  if ((r = mutt_strcasecmp ((*s)->uid, (*t)->uid)))
    return r > 0;
  else
    return mutt_strcasecmp (crypt_fpr_or_lkeyid (*s), crypt_fpr_or_lkeyid (*t)) > 0;
}