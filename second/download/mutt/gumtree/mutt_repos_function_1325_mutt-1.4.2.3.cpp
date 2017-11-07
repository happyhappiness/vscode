void imap_free_idata (IMAP_DATA** idata) {
  if (!idata)
    return;

  FREE (&(*idata)->capstr);
  mutt_free_list (&(*idata)->flags);
  FREE (&((*idata)->cmd.buf));
  FREE (idata);
}