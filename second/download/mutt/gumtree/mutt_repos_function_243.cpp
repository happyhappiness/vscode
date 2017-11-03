static int mbox_open_mailbox_append (CONTEXT *ctx, int flags)
{
  ctx->fp = safe_fopen (ctx->path, flags & MUTT_NEWFOLDER ? "w" : "a");
  if (!ctx->fp)
  {
    mutt_perror (ctx->path);
    return -1;
  }

  if (mbox_lock_mailbox (ctx, 1, 1) != 0)
  {
    mutt_error (_("Couldn't lock %s\n"), ctx->path);
    safe_fclose (&ctx->fp);
    return -1;
  }

  fseek (ctx->fp, 0, 2);

  return 0;
}