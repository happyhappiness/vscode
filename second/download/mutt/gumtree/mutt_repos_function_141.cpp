static int
perform_or (struct pattern_t *pat, pattern_exec_flag flags, CONTEXT *ctx, HEADER *hdr)
{
  for (; pat; pat = pat->next)
    if (mutt_pattern_exec (pat, flags, ctx, hdr) > 0)
      return 1;
  return 0;
}