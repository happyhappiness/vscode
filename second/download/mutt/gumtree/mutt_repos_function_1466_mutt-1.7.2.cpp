static BODY *crypt_mod_pgp_sign_message (BODY *a)
{
  return pgp_gpgme_sign_message (a);
}