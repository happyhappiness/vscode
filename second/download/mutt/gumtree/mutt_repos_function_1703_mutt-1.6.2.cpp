static pgp_key_t pgp_principal_key (pgp_key_t key)
{
  if (key->flags & KEYFLAG_SUBKEY && key->parent)
    return key->parent;
  else
    return key;
}