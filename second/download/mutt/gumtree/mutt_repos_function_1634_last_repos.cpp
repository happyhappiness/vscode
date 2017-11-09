static int
open_append_mailbox (CONTEXT *ctx, int flags)
{
  if (!ctx)
    return -1;

  /* If this succeeds, we know there's an open-hook */
  COMPRESS_INFO *ci = set_compress_info (ctx);
  if (!ci)
    return -1;

  /* To append we need an append-hook or a close-hook */
  if (!ci->append && !ci->close)
  {
    mutt_error (_("Cannot append without an append-hook or close-hook : %s"), ctx->path);
    goto oa_fail1;
  }

  if (setup_paths (ctx) != 0)
    goto oa_fail2;

  /* Lock the realpath for the duration of the append.
   * It will be unlocked in the close */
  if (!lock_realpath (ctx, 1))
  {
    mutt_error (_("Unable to lock mailbox!"));
    goto oa_fail2;
  }

  /* Open the existing mailbox, unless we are appending */
  if (!ci->append && (get_size (ctx->realpath) > 0))
  {
    int rc = execute_command (ctx, ci->open, _("Decompressing %s"));
    if (rc == 0)
    {
      mutt_error (_("Compress command failed: %s"), ci->open);
      goto oa_fail2;
    }
    ctx->magic = mx_get_magic (ctx->path);
  }
  else
    ctx->magic = DefaultMagic;

  /* We can only deal with mbox and mmdf mailboxes */
  if ((ctx->magic != MUTT_MBOX) && (ctx->magic != MUTT_MMDF))
  {
    mutt_error (_("Unsupported mailbox type for appending."));
    goto oa_fail2;
  }

  ci->child_ops = mx_get_ops (ctx->magic);
  if (!ci->child_ops)
  {
    mutt_error (_("Can't find mailbox ops for mailbox type %d"), ctx->magic);
    goto oa_fail2;
  }

  if (ci->child_ops->open_append (ctx, flags) != 0)
    goto oa_fail2;

  return 0;

oa_fail2:
  /* remove the partial uncompressed file */
  remove (ctx->path);
oa_fail1:
  /* Free the compress_info to prevent close from trying to recompress */
  mutt_free_compress_info (ctx);

  return -1;
}