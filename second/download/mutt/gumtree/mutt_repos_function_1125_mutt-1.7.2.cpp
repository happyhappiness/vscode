static int space_quotes (STATE *s)
{
  /* Allow quote spacing in the pager even for OPTTEXTFLOWED,
   * but obviously not when replying.
   */
  if (option (OPTTEXTFLOWED) && (s->flags & MUTT_REPLYING))
    return 0;

  return option (OPTREFLOWSPACEQUOTES);
}