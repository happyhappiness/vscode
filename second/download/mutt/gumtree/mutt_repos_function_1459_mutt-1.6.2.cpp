void mh_buffy(BUFFY *b)
{
  int i;
  struct mh_sequences mhs;

  b->new = 0;

  /* when $mail_check_recent is set and the .mh_sequences file hasn't changed
   * since the last mailbox visit, there is nothing to do */
  if (option(OPTMAILCHECKRECENT) && mh_sequences_changed(b) <= 0)
      return;

  memset (&mhs, 0, sizeof (mhs));

  if (mh_read_sequences (&mhs, b->path) < 0)
    return;

  /* Traverse the sequence from high to low in order to support
   * $mail_check_recent.  Given that new messages are appended, this should
   * also be faster when it is unset as well.
   */
  for (i = mhs.max; i > 0; i--)
  {
    if (mhs_check (&mhs, i) & MH_SEQ_UNSEEN)
    {
      /* if the first unseen message we encounter was in the mailbox during the last visit, don't notify about it */
      if (!option(OPTMAILCHECKRECENT) || mh_already_notified(b, i) == 0)
	b->new = 1;
      break;
    }
  }
  mhs_free_sequences (&mhs);
}