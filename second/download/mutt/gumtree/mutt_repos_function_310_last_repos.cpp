char *pgp_keyid(pgp_key_t k)
{
  k = _pgp_parent(k);

  return _pgp_keyid(k);
}