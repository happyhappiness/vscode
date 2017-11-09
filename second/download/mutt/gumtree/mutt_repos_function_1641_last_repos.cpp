int
mutt_comp_can_append (CONTEXT *ctx)
{
  if (!ctx)
    return 0;

  /* If this succeeds, we know there's an open-hook */
  COMPRESS_INFO *ci = set_compress_info (ctx);
  if (!ci)
    return 0;

  /* We have an open-hook, so to append we need an append-hook,
   * or a close-hook. */
  if (ci->append || ci->close)
    return 1;

  mutt_error (_("Cannot append without an append-hook or close-hook : %s"), ctx->path);
  return 0;
}