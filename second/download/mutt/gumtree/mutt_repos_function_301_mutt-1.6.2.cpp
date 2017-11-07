char *pgp_fingerprint(pgp_key_t k)
{
  k = _pgp_parent(k);

  return k->fingerprint;
}