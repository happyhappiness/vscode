static int eat_regexp (pattern_t *pat, BUFFER *s, BUFFER *err)
{
  BUFFER buf;
  char errmsg[STRING];
  int r;
  char *pexpr;

  mutt_buffer_init (&buf);
  pexpr = s->dptr;
  if (mutt_extract_token (&buf, s, MUTT_TOKEN_PATTERN | MUTT_TOKEN_COMMENT) != 0 ||
      !buf.data)
  {
    snprintf (err->data, err->dsize, _("Error in expression: %s"), pexpr);
    return (-1);
  }
  if (!*buf.data)
  {
    snprintf (err->data, err->dsize, _("Empty expression"));
    return (-1);
  }

#if 0
  /* If there are no RE metacharacters, use simple search anyway */
  if (!pat->stringmatch && !strpbrk (buf.data, "|[{.*+?^$"))
    pat->stringmatch = 1;
#endif

  if (pat->stringmatch)
  {
    pat->p.str = safe_strdup (buf.data);
    pat->ign_case = mutt_which_case (buf.data) == REG_ICASE;
    FREE (&buf.data);
  }
  else if (pat->groupmatch)
  {
    pat->p.g = mutt_pattern_group (buf.data);
    FREE (&buf.data);
  }
  else
  {
    pat->p.rx = safe_malloc (sizeof (regex_t));
    r = REGCOMP (pat->p.rx, buf.data, REG_NEWLINE | REG_NOSUB | mutt_which_case (buf.data));
    if (r)
    {
      regerror (r, pat->p.rx, errmsg, sizeof (errmsg));
      mutt_buffer_printf (err, "'%s': %s", buf.data, errmsg);
      FREE (&buf.data);
      FREE (&pat->p.rx);
      return (-1);
    }
    FREE (&buf.data);
  }

  return 0;
}