CONTEXT *mx_open_mailbox (const char *path, int flags, CONTEXT *pctx)
{
  CONTEXT *ctx = pctx;
  int rc;

  if (!ctx)
    ctx = safe_malloc (sizeof (CONTEXT));
  memset (ctx, 0, sizeof (CONTEXT));
  ctx->path = safe_strdup (path);

  ctx->msgnotreadyet = -1;
  ctx->collapsed = 0;
  
  if (flags & M_QUIET)
    ctx->quiet = 1;
  if (flags & M_READONLY)
    ctx->readonly = 1;

  if (flags & (M_APPEND|M_NEWFOLDER))
  {
    if (mx_open_mailbox_append (ctx, flags) != 0)
    {
      mx_fastclose_mailbox (ctx);
      if (!pctx)
	FREE (&ctx);
      return NULL;
    }
    return ctx;
  }

  ctx->magic = mx_get_magic (path);
  
  if(ctx->magic == 0)
    mutt_error (_("%s is not a mailbox."), path);

  if(ctx->magic == -1)
    mutt_perror(path);
  
  if(ctx->magic <= 0)
  {
    mx_fastclose_mailbox (ctx);
    if (!pctx)
      FREE (&ctx);
    return (NULL);
  }
  
  /* if the user has a `push' command in their .muttrc, or in a folder-hook,
   * it will cause the progress messages not to be displayed because
   * mutt_refresh() will think we are in the middle of a macro.  so set a
   * flag to indicate that we should really refresh the screen.
   */
  set_option (OPTFORCEREFRESH);

  if (!ctx->quiet)
    mutt_message (_("Reading %s..."), ctx->path);

  switch (ctx->magic)
  {
    case M_MH:
      rc = mh_read_dir (ctx, NULL);
      break;

    case M_MAILDIR:
      rc = maildir_read_dir (ctx);
      break;

    case M_MMDF:
    case M_MBOX:
      rc = mbox_open_mailbox (ctx);
      break;

#ifdef USE_IMAP
    case M_IMAP:
      rc = imap_open_mailbox (ctx);
      break;
#endif /* USE_IMAP */

#ifdef USE_POP
    case M_POP:
      rc = pop_open_mailbox (ctx);
      break;
#endif /* USE_POP */

    default:
      rc = -1;
      break;
  }

  if (rc == 0)
  {
    if ((flags & M_NOSORT) == 0)
    {
      /* avoid unnecessary work since the mailbox is completely unthreaded
	 to begin with */
      unset_option (OPTSORTSUBTHREADS);
      unset_option (OPTNEEDRESCORE);
      mutt_sort_headers (ctx, 1);
    }
    if (!ctx->quiet)
      mutt_clear_error ();
  }
  else
  {
    mx_fastclose_mailbox (ctx);
    if (!pctx)
      FREE (&ctx);
  }

  unset_option (OPTFORCEREFRESH);
  return (ctx);
}