static int _pgp_compare_address (const void *a, const void *b)
{
  int r;

  pgp_uid_t **s = (pgp_uid_t **) a;
  pgp_uid_t **t = (pgp_uid_t **) b;

  if ((r = mutt_strcasecmp ((*s)->addr, (*t)->addr)))
    return r > 0;
  else
    return (mutt_strcasecmp (pgp_fpr_or_lkeyid ((*s)->parent),
			     pgp_fpr_or_lkeyid ((*t)->parent)) > 0);
}