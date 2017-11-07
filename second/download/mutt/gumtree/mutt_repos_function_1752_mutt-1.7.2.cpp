static int crypt_mod_smime_send_menu (HEADER *msg, int *redraw)
{
  return smime_gpgme_send_menu (msg, redraw);
}