static int match_threadparent(struct pattern_t *pat, pattern_exec_flag flags, CONTEXT *ctx, THREAD *t)
{
  if (!t || !t->parent || !t->parent->message)
    return 0;

  return mutt_pattern_exec(pat, flags, ctx, t->parent->message, NULL);
}