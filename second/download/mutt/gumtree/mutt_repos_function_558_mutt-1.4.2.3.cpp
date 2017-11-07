int mutt_chscmp (const char *s, const char *chs)
{
  char buffer[STRING];

  if (!s) return 0;

  mutt_canonical_charset (buffer, sizeof (buffer), s);
  return !ascii_strcasecmp (buffer, chs);
}