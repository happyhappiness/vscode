int mutt_parse_score (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  SCORE *ptr, *last;
  char *pattern, *pc;
  struct pattern_t *pat;

  mutt_extract_token (buf, s, 0);
  if (!MoreArgs (s))
  {
    strfcpy (err->data, _("score: too few arguments"), err->dsize);
    return (-1);
  }
  pattern = buf->data;
  memset (buf, 0, sizeof (BUFFER));
  mutt_extract_token (buf, s, 0);
  if (MoreArgs (s))
  {
    FREE (&pattern);
    strfcpy (err->data, _("score: too many arguments"), err->dsize);
    return (-1);
  }

  /* look for an existing entry and update the value, else add it to the end
     of the list */
  for (ptr = Score, last = NULL; ptr; last = ptr, ptr = ptr->next)
    if (mutt_strcmp (pattern, ptr->str) == 0)
      break;
  if (!ptr)
  {
    if ((pat = mutt_pattern_comp (pattern, 0, err)) == NULL)
    {
      FREE (&pattern);
      return (-1);
    }
    ptr = safe_calloc (1, sizeof (SCORE));
    if (last)
      last->next = ptr;
    else
      Score = ptr;
    ptr->pat = pat;
    ptr->str = pattern;
  }
  pc = buf->data;
  if (*pc == '=')
  {
    ptr->exact = 1;
    pc++;
  }
  ptr->val = atoi (pc);
  set_option (OPTNEEDRESCORE);
  return 0;
}