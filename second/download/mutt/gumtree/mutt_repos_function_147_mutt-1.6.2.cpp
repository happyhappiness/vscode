static int match_threadcomplete(struct pattern_t *pat, pattern_exec_flag flags, CONTEXT *ctx, THREAD *t,int left,int up,int right,int down)
{
  int a;
  HEADER *h;

  if(!t)
    return 0;
  h = t->message;
  if(h)
    if(mutt_pattern_exec(pat, flags, ctx, h))
      return 1;

  if(up && (a=match_threadcomplete(pat, flags, ctx, t->parent,1,1,1,0)))
    return a;
  if(right && t->parent && (a=match_threadcomplete(pat, flags, ctx, t->next,0,0,1,1)))
    return a;
  if(left && t->parent && (a=match_threadcomplete(pat, flags, ctx, t->prev,1,0,0,1)))
    return a;
  if(down && (a=match_threadcomplete(pat, flags, ctx, t->child,1,0,1,1)))
    return a;
  return 0;
}