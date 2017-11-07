void imap_keepalive (void)
{
  CONTEXT *ctx = Context;
  
  if (ctx == NULL || ctx->magic != M_IMAP || CTX_DATA->ctx != ctx)
    return;

  imap_check_mailbox (ctx, NULL);
}