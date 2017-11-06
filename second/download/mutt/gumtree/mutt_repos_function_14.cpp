static char *crypt_mod_smime_findkeys (ADDRESS *adrlist, int oppenc_mode)
{
  return smime_findKeys (adrlist, oppenc_mode);
}