void pgp_free_key (pgp_key_t *kpp)
{
  pgp_key_t p, q, r;

  if (!kpp || !*kpp)
    return;

  if ((*kpp)->parent && (*kpp)->parent != *kpp)
    *kpp = (*kpp)->parent;
  
  /* Order is important here:
   *
   * - First free all children.
   * - If we are an orphan (i.e., our parent was not in the key list),
   *   free our parent.
   * - free ourselves.
   */

  for (p = *kpp; p; p = q)
  {
    for (q = p->next; q && q->parent == p; q = r)
    {
      r = q->next;
      _pgp_free_key (&q);
    }
    if (p->parent)
      _pgp_free_key (&p->parent);

    _pgp_free_key (&p);
  }

  *kpp = NULL;
}