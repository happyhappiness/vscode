static int mh_sync_message (CONTEXT *ctx, int msgno)
{
  HEADER *h = ctx->hdrs[msgno];

  if (h->attach_del)
    if (mh_rewrite_message (ctx, msgno) != 0)
      return -1;
  
  return 0;
}