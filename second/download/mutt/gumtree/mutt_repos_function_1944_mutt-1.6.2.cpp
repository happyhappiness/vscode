void imap_allow_reopen (CONTEXT *ctx)
{
  if (ctx && ctx->magic == M_IMAP && CTX_DATA->ctx == ctx)
    CTX_DATA->reopen |= IMAP_REOPEN_ALLOW;
}