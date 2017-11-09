int smime_gpgme_send_menu (HEADER *msg)
{
  return gpgme_send_menu (msg, 1);
}