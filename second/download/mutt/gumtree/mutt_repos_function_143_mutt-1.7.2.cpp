static int match_reference (pattern_t *pat, LIST *refs)
{
  for (; refs; refs = refs->next)
    if (patmatch (pat, refs->data) == 0)
      return 1;
  return 0;
}