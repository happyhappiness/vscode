static pgp_key_t _pgp_parent(pgp_key_t k)
{
  if((k->flags & KEYFLAG_SUBKEY) && k->parent && option(OPTPGPIGNORESUB))
    k = k->parent;

  return k;
}