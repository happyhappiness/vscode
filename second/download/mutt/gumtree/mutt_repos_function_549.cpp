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
  mutt_buffer_init (buf);
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
  } else
    /* 'buf' arg was cleared and 'pattern' holds the only reference;
     * as here 'ptr' != NULL -> update the value only in which case
     * ptr->str already has the string, so pattern should be freed.
     */
    FREE (&pattern);
  pc = buf->data;
  if (*pc == '=')
  {
    ptr->exact = 1;
    pc++;
  }
  if (mutt_atoi (pc, &ptr->val) < 0)
  {
    FREE (&pattern);
    strfcpy (err->data, _("Error: score: invalid number"), err->dsize);
    return (-1);
  }
  set_option (OPTNEEDRESCORE);
  return 0;
}