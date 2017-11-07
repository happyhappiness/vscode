static int crypt_mod_pgp_send_menu (HEADER *msg, int *redraw)
{
  return pgp_gpgme_send_menu (msg, redraw);
}