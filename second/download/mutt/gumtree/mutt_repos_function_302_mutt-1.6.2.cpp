char *pgp_fpr_or_lkeyid(pgp_key_t k)
{
  char *fingerprint;

  fingerprint = pgp_fingerprint (k);
  return fingerprint ? fingerprint : pgp_long_keyid (k);
}