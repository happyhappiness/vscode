static int _pgp_compare_trust (const void *a, const void *b)
{
  int r;

  pgp_uid_t **s = (pgp_uid_t **) a;
  pgp_uid_t **t = (pgp_uid_t **) b;

  if ((r = (((*s)->parent->flags & (KEYFLAG_RESTRICTIONS))
	    - ((*t)->parent->flags & (KEYFLAG_RESTRICTIONS)))))
    return r > 0;
  if ((r = ((*s)->trust - (*t)->trust)))
    return r < 0;
  if ((r = ((*s)->parent->keylen - (*t)->parent->keylen)))
    return r < 0;
  if ((r = ((*s)->parent->gen_time - (*t)->parent->gen_time)))
    return r < 0;
  if ((r = mutt_strcasecmp ((*s)->addr, (*t)->addr)))
    return r > 0;
  return (mutt_strcasecmp (pgp_fpr_or_lkeyid ((*s)->parent), 
			   pgp_fpr_or_lkeyid ((*t)->parent))) > 0;
}