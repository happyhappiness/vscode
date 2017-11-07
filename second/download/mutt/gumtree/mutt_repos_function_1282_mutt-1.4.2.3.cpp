static void cmd_make_sequence (IMAP_DATA* idata)
{
  snprintf (idata->cmd.seq, sizeof (idata->cmd.seq), "a%04d", idata->seqno++);

  if (idata->seqno > 9999)
    idata->seqno = 0;
}