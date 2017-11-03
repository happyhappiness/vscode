int mutt_parse_unscore (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  SCORE *tmp, *last = NULL;

  while (MoreArgs (s))
  {
    mutt_extract_token (buf, s, 0);
    if (!mutt_strcmp ("*", buf->data))
    {
      for (tmp = Score; tmp; )
      {
	last = tmp;
	tmp = tmp->next;
	mutt_pattern_free (&last->pat);
	FREE (&last);
      }
      Score = NULL;
    }
    else
    {
      for (tmp = Score; tmp; last = tmp, tmp = tmp->next)
      {
	if (!mutt_strcmp (buf->data, tmp->str))
	{
	  if (last)
	    last->next = tmp->next;
	  else
	    Score = tmp->next;
	  mutt_pattern_free (&tmp->pat);
	  FREE (&tmp);
	  /* there should only be one score per pattern, so we can stop here */
	  break;
	}
      }
    }
  }
  set_option (OPTNEEDRESCORE);
  return 0;
}