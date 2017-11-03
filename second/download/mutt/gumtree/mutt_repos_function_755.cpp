char *smime_gpgme_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  return find_keys (adrlist, APPLICATION_SMIME, oppenc_mode);
}