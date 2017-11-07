int mutt_link_threads (HEADER *cur, HEADER *last, CONTEXT *ctx)
{
  int i, changed = 0;

  if (!last)
  {
    for (i = 0; i < ctx->vcount; i++)
      if (ctx->hdrs[Context->v2r[i]]->tagged)
	changed |= link_threads (cur, ctx->hdrs[Context->v2r[i]], ctx);
  }
  else
    changed = link_threads (cur, last, ctx);

  return changed;
}