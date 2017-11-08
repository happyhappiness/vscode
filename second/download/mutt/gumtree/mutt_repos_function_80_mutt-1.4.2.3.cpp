int eat_regexp (pattern_t *pat, BUFFER *s, BUFFER *err)
{
  BUFFER buf;
  int r;

  memset (&buf, 0, sizeof (buf));
  if (mutt_extract_token (&buf, s, M_TOKEN_PATTERN | M_TOKEN_COMMENT) != 0 ||
      !buf.data)
  {
    snprintf (err->data, err->dsize, _("Error in expression: %s"), s->dptr);
    return (-1);
  }
  pat->rx = safe_malloc (sizeof (regex_t));
  r = REGCOMP (pat->rx, buf.data, REG_NEWLINE | REG_NOSUB | mutt_which_case (buf.data));
  FREE (&buf.data);
  if (r)
  {
    regerror (r, pat->rx, err->data, err->dsize);
    regfree (pat->rx);
    safe_free ((void **) &pat->rx);
    return (-1);
  }
  return 0;
}