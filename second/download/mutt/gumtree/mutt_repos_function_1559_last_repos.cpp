static int maildir_add_to_context (CONTEXT * ctx, struct maildir *md)
{
  int oldmsgcount = ctx->msgcount;

  while (md)
  {

    dprint (2, (debugfile, "%s:%d maildir_add_to_context(): Considering %s\n",
		__FILE__, __LINE__, NONULL (md->canon_fname)));

    if (md->h)
    {
      dprint (2,
	      (debugfile,
	       "%s:%d Adding header structure. Flags: %s%s%s%s%s\n", __FILE__,
	       __LINE__, md->h->flagged ? "f" : "", md->h->deleted ? "D" : "",
	       md->h->replied ? "r" : "", md->h->old ? "O" : "",
	       md->h->read ? "R" : ""));
      if (ctx->msgcount == ctx->hdrmax)
	mx_alloc_memory (ctx);

      ctx->hdrs[ctx->msgcount] = md->h;
      ctx->hdrs[ctx->msgcount]->index = ctx->msgcount;
      ctx->size +=
	md->h->content->length + md->h->content->offset -
	md->h->content->hdr_offset;

      md->h = NULL;
      ctx->msgcount++;
    }
    md = md->next;
  }

  if (ctx->msgcount > oldmsgcount)
  {
    mx_update_context (ctx, ctx->msgcount - oldmsgcount);
    return 1;
  }
  return 0;
}