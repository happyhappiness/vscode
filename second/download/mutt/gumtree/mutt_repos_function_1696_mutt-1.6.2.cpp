static BODY *crypt_mod_smime_sign_message (BODY *a)
{
  return smime_gpgme_sign_message (a);
}