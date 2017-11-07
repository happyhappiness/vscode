static BODY *crypt_mod_pgp_make_key_attachment (char *tempf)
{
  return pgp_gpgme_make_key_attachment (tempf);
}