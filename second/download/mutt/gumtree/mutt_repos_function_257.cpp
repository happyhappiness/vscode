static int mbox_has_new(CONTEXT *ctx)
{
  int i;

  for (i = 0; i < ctx->msgcount; i++)
    if (!ctx->hdrs[i]->deleted && !ctx->hdrs[i]->read && !ctx->hdrs[i]->old)
      return 1;
  return 0;
}