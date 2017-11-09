pgp_key_t pgp_remove_key (pgp_key_t *klist, pgp_key_t key)
{
  pgp_key_t *last;
  pgp_key_t p, q, r;

  if (!klist || !*klist || !key)
    return NULL;

  if (key->parent && key->parent != key)
    key = key->parent;

  last = klist;
  for (p = *klist; p && p != key; p = p->next)
    last = &p->next;

  if (!p)
    return NULL;

  for (q = p->next, r = p; q && q->parent == p; q = q->next)
    r = q;

  if (r)
    r->next = NULL;

  *last = q;
  return q;
}