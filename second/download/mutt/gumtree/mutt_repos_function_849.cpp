int mutt_edit_message (CONTEXT *ctx, HEADER *hdr)
{
  int i, j;

  if (hdr)
    return edit_one_message (ctx, hdr);

  
  for (i = 0; i < ctx->vcount; i++)
  {
    j = ctx->v2r[i];
    if (ctx->hdrs[j]->tagged)
    {
      if (edit_one_message (ctx, ctx->hdrs[j]) == -1)
	return -1;
    }
  }

  return 0;
}