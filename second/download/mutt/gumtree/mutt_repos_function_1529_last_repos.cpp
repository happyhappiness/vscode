static char *crypt_mod_pgp_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  return pgp_gpgme_findkeys (adrlist, oppenc_mode);
}