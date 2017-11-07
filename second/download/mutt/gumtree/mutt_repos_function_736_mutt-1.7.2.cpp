static int _crypt_compare_trust (const void *a, const void *b)
{
  crypt_key_t **s = (crypt_key_t **) a;
  crypt_key_t **t = (crypt_key_t **) b;
  unsigned long ts = 0, tt = 0;
  int r;

  if ((r = (((*s)->flags & (KEYFLAG_RESTRICTIONS))
	    - ((*t)->flags & (KEYFLAG_RESTRICTIONS)))))
    return r > 0;

  ts = (*s)->validity;
  tt = (*t)->validity;
  if ((r = (tt - ts)))
    return r < 0;

  if ((*s)->kobj->subkeys)
    ts = (*s)->kobj->subkeys->length;
  if ((*t)->kobj->subkeys)
    tt = (*t)->kobj->subkeys->length;
  if (ts != tt)
    return ts > tt;

  if ((*s)->kobj->subkeys && ((*s)->kobj->subkeys->timestamp > 0))
    ts = (*s)->kobj->subkeys->timestamp;
  if ((*t)->kobj->subkeys && ((*t)->kobj->subkeys->timestamp > 0))
    tt = (*t)->kobj->subkeys->timestamp;
  if (ts > tt)
    return 1;
  if (ts < tt)
    return 0;

  if ((r = mutt_strcasecmp ((*s)->uid, (*t)->uid)))
    return r > 0;
  return (mutt_strcasecmp (crypt_fpr_or_lkeyid ((*s)), crypt_fpr_or_lkeyid ((*t)))) > 0;
}