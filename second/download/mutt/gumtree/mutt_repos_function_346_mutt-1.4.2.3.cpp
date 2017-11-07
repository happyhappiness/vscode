int mx_check_mailbox (CONTEXT *ctx, int *index_hint, int lock)
{
  int rc;

  if (ctx)
  {
    if (ctx->locked) lock = 0;

    switch (ctx->magic)
    {
      case M_MBOX:
      case M_MMDF:

	if (lock)
	{
	  mutt_block_signals ();
	  if (mbox_lock_mailbox (ctx, 0, 0) == -1)
	  {
	    mutt_unblock_signals ();
	    return M_LOCKED;
	  }
	}
	
	rc = mbox_check_mailbox (ctx, index_hint);

	if (lock)
	{
	  mutt_unblock_signals ();
	  mbox_unlock_mailbox (ctx);
	}
	
	return rc;


      case M_MH:
      case M_MAILDIR:
	return (mh_check_mailbox (ctx, index_hint));

#ifdef USE_IMAP
      case M_IMAP:
	return (imap_check_mailbox (ctx, index_hint));
#endif /* USE_IMAP */

#ifdef USE_POP
      case M_POP:
	return (pop_check_mailbox (ctx, index_hint));
#endif /* USE_POP */
    }
  }

  dprint (1, (debugfile, "mx_check_mailbox: null or invalid context.\n"));
  return (-1);
}