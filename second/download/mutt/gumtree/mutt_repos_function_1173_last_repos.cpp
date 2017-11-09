static int add_quote_suffix (STATE *s, int ql)
{
  if (s->flags & MUTT_REPLYING)
    return 0;

  if (space_quotes (s))
    return 0;

  if (!ql && !s->prefix)
    return 0;

  /* The prefix will add its own space */
  if (!option (OPTTEXTFLOWED) && !ql && s->prefix)
    return 0;

  return 1;
}