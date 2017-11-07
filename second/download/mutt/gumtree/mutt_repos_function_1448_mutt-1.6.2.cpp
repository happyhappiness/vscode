static void crypt_mod_pgp_set_sender (const char *sender)
{
  gpgme_set_sender (sender);
}