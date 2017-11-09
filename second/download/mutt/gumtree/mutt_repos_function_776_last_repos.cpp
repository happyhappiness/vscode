char *pgp_gpgme_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  return find_keys (adrlist, APPLICATION_PGP, oppenc_mode);
}