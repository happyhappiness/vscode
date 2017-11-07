static int set_pgp_flags (HEADER *cur, CONTEXT *ctx)
{
  int i;
  int flags = 0;
  
  if (cur) 
    return _set_pgp_flags (cur);
  
  if (!ctx)
    return 0;
    
  for (i = 0; i < ctx->vcount; i++)
  {
    cur = ctx->hdrs[ctx->v2r[i]];
    if (cur->tagged)
      flags |= _set_pgp_flags (cur);
  }

  return flags;
}