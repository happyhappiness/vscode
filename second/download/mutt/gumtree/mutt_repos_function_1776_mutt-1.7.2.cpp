static pgp_key_t *pgp_get_lastp (pgp_key_t p)
{
  for (; p; p = p->next)
    if (!p->next)
      return &p->next;

  return NULL;
}