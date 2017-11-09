static int mbox_check_mailbox (CONTEXT *ctx, int *index_hint)
{
  struct stat st;
  char buffer[LONG_STRING];
  int unlock = 0;
  int modified = 0;

  if (stat (ctx->path, &st) == 0)
  {
    if (st.st_mtime == ctx->mtime && st.st_size == ctx->size)
      return (0);

    if (st.st_size == ctx->size)
    {
      /* the file was touched, but it is still the same length, so just exit */
      ctx->mtime = st.st_mtime;
      return (0);
    }

    if (st.st_size > ctx->size)
    {
      /* lock the file if it isn't already */
      if (!ctx->locked)
      {
	mutt_block_signals ();
	if (mbox_lock_mailbox (ctx, 0, 0) == -1)
	{
	  mutt_unblock_signals ();
	  /* we couldn't lock the mailbox, but nothing serious happened:
	   * probably the new mail arrived: no reason to wait till we can
	   * parse it: we'll get it on the next pass
	   */
	  return (MUTT_LOCKED);
	}
	unlock = 1;
      }

      /*
       * Check to make sure that the only change to the mailbox is that 
       * message(s) were appended to this file.  My heuristic is that we should
       * see the message separator at *exactly* what used to be the end of the
       * folder.
       */
      if (fseeko (ctx->fp, ctx->size, SEEK_SET) != 0)
	dprint (1, (debugfile, "mbox_check_mailbox: fseek() failed\n"));
      if (fgets (buffer, sizeof (buffer), ctx->fp) != NULL)
      {
	if ((ctx->magic == MUTT_MBOX && mutt_strncmp ("From ", buffer, 5) == 0) ||
	    (ctx->magic == MUTT_MMDF && mutt_strcmp (MMDF_SEP, buffer) == 0))
	{
	  if (fseeko (ctx->fp, ctx->size, SEEK_SET) != 0)
	    dprint (1, (debugfile, "mbox_check_mailbox: fseek() failed\n"));
	  if (ctx->magic == MUTT_MBOX)
	    mbox_parse_mailbox (ctx);
	  else
	    mmdf_parse_mailbox (ctx);

	  /* Only unlock the folder if it was locked inside of this routine.
	   * It may have been locked elsewhere, like in
	   * mutt_checkpoint_mailbox().
	   */

	  if (unlock)
	  {
	    mbox_unlock_mailbox (ctx);
	    mutt_unblock_signals ();
	  }

	  return (MUTT_NEW_MAIL); /* signal that new mail arrived */
	}
	else
	  modified = 1;
      }
      else
      {
	dprint (1, (debugfile, "mbox_check_mailbox: fgets returned NULL.\n"));
	modified = 1;
      }
    }
    else
      modified = 1;
  }

  if (modified)
  {
    if (mutt_reopen_mailbox (ctx, index_hint) != -1)
    {
      if (unlock)
      {
	mbox_unlock_mailbox (ctx);
	mutt_unblock_signals ();
      }
      return (MUTT_REOPENED);
    }
  }

  /* fatal error */

  mbox_unlock_mailbox (ctx);
  mx_fastclose_mailbox (ctx);
  mutt_unblock_signals ();
  mutt_error _("Mailbox was corrupted!");
  return (-1);
}