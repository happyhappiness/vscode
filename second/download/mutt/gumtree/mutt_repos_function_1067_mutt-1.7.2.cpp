void pgp_free_uid (pgp_uid_t ** upp)
{
  pgp_uid_t *up, *q;

  if (!upp || !*upp)
    return;
  for (up = *upp; up; up = q)
  {
    q = up->next;
    pgp_free_sig (&up->sigs);
    FREE (&up->addr);
    FREE (&up);
  }

  *upp = NULL;
}