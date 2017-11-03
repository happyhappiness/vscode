static int trash_append (CONTEXT *ctx)
{
  CONTEXT ctx_trash;
  int i;
  struct stat st, stc;
  int opt_confappend, rc;

  if (!TrashPath || !ctx->deleted ||
      (ctx->magic == MUTT_MAILDIR && option (OPTMAILDIRTRASH)))
    return 0;

  for (i = 0; i < ctx->msgcount; i++)
    if (ctx->hdrs[i]->deleted  && (!ctx->hdrs[i]->purge))
      break;
  if (i == ctx->msgcount)
    return 0; /* nothing to be done */

  /* avoid the "append messages" prompt */
  opt_confappend = option (OPTCONFIRMAPPEND);
  if (opt_confappend)
    unset_option (OPTCONFIRMAPPEND);
  rc = mutt_save_confirm (TrashPath, &st);
  if (opt_confappend)
    set_option (OPTCONFIRMAPPEND);
  if (rc != 0)
  {
    mutt_error _("message(s) not deleted");
    return -1;
  }

  if (lstat (ctx->path, &stc) == 0 && stc.st_ino == st.st_ino
      && stc.st_dev == st.st_dev && stc.st_rdev == st.st_rdev)
    return 0;  /* we are in the trash folder: simple sync */

#ifdef USE_IMAP
  if (Context->magic == MUTT_IMAP && mx_is_imap (TrashPath))
  {
    if (!imap_fast_trash (Context, TrashPath))
      return 0;
  }
#endif

  if (mx_open_mailbox (TrashPath, MUTT_APPEND, &ctx_trash) != NULL)
  {
    /* continue from initial scan above */
    for (; i < ctx->msgcount ; i++)
      if (ctx->hdrs[i]->deleted  && (!ctx->hdrs[i]->purge))
      {
        if (mutt_append_message (&ctx_trash, ctx, ctx->hdrs[i], 0, 0) == -1)
        {
          mx_close_mailbox (&ctx_trash, NULL);
          return -1;
        }
      }

    mx_close_mailbox (&ctx_trash, NULL);
  }
  else
  {
    mutt_error _("Can't open trash folder");
    return -1;
  }

  return 0;
}