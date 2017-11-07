char *pgp_keyid(pgp_key_t *k)
{
  if((k->flags & KEYFLAG_SUBKEY) && k->parent)
    k = k->parent;

  return _pgp_keyid(k);
}