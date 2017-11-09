static int
open_mailbox (CONTEXT *ctx)
{
  if (!ctx || (ctx->magic != MUTT_COMPRESSED))
    return -1;

  COMPRESS_INFO *ci = set_compress_info (ctx);
  if (!ci)
    return -1;

  /* If there's no close-hook, or the file isn't writable */
  if (!ci->close || (access (ctx->path, W_OK) != 0))
    ctx->readonly = 1;

  if (setup_paths (ctx) != 0)
    goto or_fail;
  store_size (ctx);

  if (!lock_realpath (ctx, 0))
  {
    mutt_error (_("Unable to lock mailbox!"));
    goto or_fail;
  }

  int rc = execute_command (ctx, ci->open, _("Decompressing %s"));
  if (rc == 0)
    goto or_fail;

  unlock_realpath (ctx);

  ctx->magic = mx_get_magic (ctx->path);
  if (ctx->magic == 0)
  {
    mutt_error (_("Can't identify the contents of the compressed file"));
    goto or_fail;
  }

  ci->child_ops = mx_get_ops (ctx->magic);
  if (!ci->child_ops)
  {
    mutt_error (_("Can't find mailbox ops for mailbox type %d"), ctx->magic);
    goto or_fail;
  }

  return ci->child_ops->open (ctx);

or_fail:
  /* remove the partial uncompressed file */
  remove (ctx->path);
  mutt_free_compress_info (ctx);
  return -1;
}