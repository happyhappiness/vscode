int pgp_gpgme_send_menu (HEADER *msg, int *redraw)
{
  return gpgme_send_menu (msg, redraw, 0);
}