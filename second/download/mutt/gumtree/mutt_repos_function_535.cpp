static int sync_mailbox (CONTEXT *ctx, int *index_hint)
{
  BUFFY *tmp = NULL;
  int rc = -1;

  if (!ctx->quiet)
    mutt_message (_("Writing %s..."), ctx->path);

  switch (ctx->magic)
  {
    case MUTT_MBOX:
    case MUTT_MMDF:
      rc = mbox_sync_mailbox (ctx, index_hint);
      if (option(OPTCHECKMBOXSIZE))
	tmp = mutt_find_mailbox (ctx->path);
      break;
      
    case MUTT_MH:
    case MUTT_MAILDIR:
      rc = mh_sync_mailbox (ctx, index_hint);
      break;
      
#ifdef USE_IMAP
    case MUTT_IMAP:
      /* extra argument means EXPUNGE */
      rc = imap_sync_mailbox (ctx, 1, index_hint);
      break;
#endif /* USE_IMAP */

#ifdef USE_POP
    case MUTT_POP:
      rc = pop_sync_mailbox (ctx, index_hint);
      break;
#endif /* USE_POP */
  }

#if 0
  if (!ctx->quiet && !ctx->shutup && rc == -1)
    mutt_error ( _("Could not synchronize mailbox %s!"), ctx->path);
#endif
  
  if (tmp && tmp->new == 0)
    mutt_update_mailbox (tmp);
  return rc;
}