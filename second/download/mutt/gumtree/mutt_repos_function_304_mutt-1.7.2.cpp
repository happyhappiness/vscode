char *pgp_short_keyid(pgp_key_t k)
{
  k = _pgp_parent(k);

  return k->keyid + 8;
}