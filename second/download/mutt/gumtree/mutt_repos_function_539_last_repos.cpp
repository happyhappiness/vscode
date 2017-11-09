CONTEXT *mx_open_mailbox (const char *path, int flags, CONTEXT *pctx)
{
  CONTEXT *ctx = pctx;
  int rc;

  if (!ctx)
    ctx = safe_malloc (sizeof (CONTEXT));
  memset (ctx, 0, sizeof (CONTEXT));

  ctx->path = safe_strdup (path);
  if (!ctx->path)
  {
    if (!pctx)
      FREE (&ctx);
    return NULL;
  }
  if (! (ctx->realpath = realpath (ctx->path, NULL)) )
    ctx->realpath = safe_strdup (ctx->path);

  ctx->msgnotreadyet = -1;
  ctx->collapsed = 0;

  for (rc=0; rc < RIGHTSMAX; rc++)
    mutt_bit_set(ctx->rights,rc);

  if (flags & MUTT_QUIET)
    ctx->quiet = 1;
  if (flags & MUTT_READONLY)
    ctx->readonly = 1;
  if (flags & MUTT_PEEK)
    ctx->peekonly = 1;

  if (flags & (MUTT_APPEND|MUTT_NEWFOLDER))
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
  ctx->mx_ops = mx_get_ops (ctx->magic);

  if (ctx->magic <= 0 || !ctx->mx_ops)
  {
    if (ctx->magic == -1)
      mutt_perror(path);
    else if (ctx->magic == 0 || !ctx->mx_ops)
      mutt_error (_("%s is not a mailbox."), path);

    mx_fastclose_mailbox (ctx);
    if (!pctx)
      FREE (&ctx);
    return (NULL);
  }

  mutt_make_label_hash (ctx);

  /* if the user has a `push' command in their .muttrc, or in a folder-hook,
   * it will cause the progress messages not to be displayed because
   * mutt_refresh() will think we are in the middle of a macro.  so set a
   * flag to indicate that we should really refresh the screen.
   */
  set_option (OPTFORCEREFRESH);

  if (!ctx->quiet)
    mutt_message (_("Reading %s..."), ctx->path);

  rc = ctx->mx_ops->open(ctx);

  if (rc == 0)
  {
    if ((flags & MUTT_NOSORT) == 0)
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