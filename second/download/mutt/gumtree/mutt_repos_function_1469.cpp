static BODY *crypt_mod_pgp_encrypt_message (BODY *a, char *keylist, int sign)
{
  return pgp_gpgme_encrypt_message (a, keylist, sign);
}