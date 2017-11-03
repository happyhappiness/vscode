static int _pgp_compare_date (const void *a, const void *b)
{
  int r;
  pgp_uid_t **s = (pgp_uid_t **) a;
  pgp_uid_t **t = (pgp_uid_t **) b;

  if ((r = ((*s)->parent->gen_time - (*t)->parent->gen_time)))
    return r > 0;
  return (mutt_strcasecmp ((*s)->addr, (*t)->addr)) > 0;
}