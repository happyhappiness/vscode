void mutt_set_virtual (CONTEXT *ctx)
{
  int i;
  HEADER *cur;

  ctx->vcount = 0;
  ctx->vsize = 0;

  for (i = 0; i < ctx->msgcount; i++)
  {
    cur = ctx->hdrs[i];
    if (cur->virtual >= 0)
    {
      cur->virtual = ctx->vcount;
      ctx->v2r[ctx->vcount] = i;
      ctx->vcount++;
      ctx->vsize += cur->content->length + cur->content->offset - cur->content->hdr_offset;
      cur->num_hidden = mutt_get_hidden (ctx, cur);
    }
  }
}