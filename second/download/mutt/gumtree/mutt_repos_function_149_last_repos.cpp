static int match_threadchildren(struct pattern_t *pat, pattern_exec_flag flags, CONTEXT *ctx, THREAD *t)
{
  if (!t || !t->child)
    return 0;

  for (t = t->child; t; t = t->next)
    if (t->message && mutt_pattern_exec(pat, flags, ctx, t->message, NULL))
      return 1;

  return 0;
}