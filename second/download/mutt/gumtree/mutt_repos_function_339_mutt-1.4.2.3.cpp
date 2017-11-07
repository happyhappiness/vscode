static int sync_mailbox (CONTEXT *ctx, int *index_hint)
{
#ifdef BUFFY_SIZE
  BUFFY *tmp = NULL;
#endif
  int rc = -1;

  if (!ctx->quiet)
    mutt_message (_("Writing %s..."), ctx->path);

  switch (ctx->magic)
  {
    case M_MBOX:
    case M_MMDF:
      rc = mbox_sync_mailbox (ctx, index_hint);
#ifdef BUFFY_SIZE
      tmp = mutt_find_mailbox (ctx->path);
#endif
      break;
      
    case M_MH:
    case M_MAILDIR:
      rc = mh_sync_mailbox (ctx, index_hint);
      break;
      
#ifdef USE_IMAP
    case M_IMAP:
      /* extra argument means EXPUNGE */
      rc = imap_sync_mailbox (ctx, 1, index_hint);
      break;
#endif /* USE_IMAP */

#ifdef USE_POP
    case M_POP:
      rc = pop_sync_mailbox (ctx, index_hint);
      break;
#endif /* USE_POP */
  }

#if 0
  if (!ctx->quiet && !ctx->shutup && rc == -1)
    mutt_error ( _("Could not synchronize mailbox %s!"), ctx->path);
#endif
  
#ifdef BUFFY_SIZE
  if (tmp && tmp->new == 0)
    mutt_update_mailbox (tmp);
#endif
  return rc;
}