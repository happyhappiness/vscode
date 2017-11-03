int mutt_chscmp (const char *s, const char *chs)
{
  char buffer[STRING];
  int a, b;

  if (!s) return 0;

  /* charsets may have extensions mutt_canonical_charset()
     leaves intact; we expect `chs' to originate from mutt
     code, not user input (i.e. `chs' does _not_ have any
     extension)
     we simply check if the shorter string is a prefix for
     the longer */
  mutt_canonical_charset (buffer, sizeof (buffer), s);
  a = mutt_strlen (buffer);
  b = mutt_strlen (chs);
  return !ascii_strncasecmp (a > b ? buffer : chs,
			     a > b ? chs : buffer, MIN(a,b));
}