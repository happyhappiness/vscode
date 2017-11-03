const char *pgp_micalg (const char *fname)
{
  return pgp_hash_to_micalg (pgp_find_hash (fname));
}