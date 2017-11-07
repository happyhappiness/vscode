static int _crypt_compare_date (const void *a, const void *b)
{
  crypt_key_t **s = (crypt_key_t **) a;
  crypt_key_t **t = (crypt_key_t **) b;
  unsigned long ts = 0, tt = 0;

  if ((*s)->kobj->subkeys && ((*s)->kobj->subkeys->timestamp > 0))
    ts = (*s)->kobj->subkeys->timestamp;
  if ((*t)->kobj->subkeys && ((*t)->kobj->subkeys->timestamp > 0))
    tt = (*t)->kobj->subkeys->timestamp;

  if (ts > tt)
    return 1;
  if (ts < tt)
    return 0;

  return mutt_strcasecmp ((*s)->uid, (*t)->uid) > 0;
}