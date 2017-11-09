static int
close_mailbox (CONTEXT *ctx)
{
  if (!ctx)
    return -1;

  COMPRESS_INFO *ci = ctx->compress_info;
  if (!ci)
    return -1;

  struct mx_ops *ops = ci->child_ops;
  if (!ops)
    return -1;

  ops->close (ctx);

  /* sync has already been called, so we only need to delete some files */
  if (!ctx->append)
  {
    /* If the file was removed, remove the compressed folder too */
    if ((access (ctx->path, F_OK) != 0) && !option (OPTSAVEEMPTY))
    {
      remove (ctx->realpath);
    }
    else
    {
      remove (ctx->path);
    }

    return 0;
  }

  const char *append;
  const char *msg;

  /* The file exists and we can append */
  if ((access (ctx->realpath, F_OK) == 0) && ci->append)
  {
    append = ci->append;
    msg = _("Compressed-appending to %s...");
  }
  else
  {
    append = ci->close;
    msg = _("Compressing %s...");
  }

  int rc = execute_command (ctx, append, msg);
  if (rc == 0)
  {
    mutt_any_key_to_continue (NULL);
    mutt_error (_("Error. Preserving temporary file: %s"), ctx->path);
  }
  else
    remove (ctx->path);

  unlock_realpath (ctx);

  return 0;
}