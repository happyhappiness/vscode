int imap_code (const char *s)
{
  s += SEQLEN;
  SKIPWS (s);
  return (ascii_strncasecmp ("OK", s, 2) == 0);
}