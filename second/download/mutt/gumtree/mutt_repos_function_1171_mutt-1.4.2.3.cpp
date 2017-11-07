static int _pgp_compare_keyid (const void *a, const void *b)
{
  int r;

  pgp_uid_t **s = (pgp_uid_t **) a;
  pgp_uid_t **t = (pgp_uid_t **) b;

  if ((r = mutt_strcasecmp (_pgp_keyid ((*s)->parent), 
			    _pgp_keyid ((*t)->parent))))
    return r > 0;
  else
    return (mutt_strcasecmp ((*s)->addr, (*t)->addr)) > 0;
}