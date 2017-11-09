pgp_uid_t *pgp_copy_uids (pgp_uid_t *up, pgp_key_t parent)
{
  pgp_uid_t *l = NULL;
  pgp_uid_t **lp = &l;

  for (; up; up = up->next)
  {
    *lp = safe_calloc (1, sizeof (pgp_uid_t));
    (*lp)->trust  = up->trust;
    (*lp)->flags  = up->flags;
    (*lp)->addr   = safe_strdup (up->addr);
    (*lp)->parent = parent;
    lp = &(*lp)->next;
  }

  return l;
}