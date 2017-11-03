static BODY *crypt_mod_smime_build_smime_entity (BODY *a, char *certlist)
{
  return smime_gpgme_build_smime_entity (a, certlist);
}