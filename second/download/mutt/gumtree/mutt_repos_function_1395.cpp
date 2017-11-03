void mutt_display_sanitize (char *s)
{
  for (; *s; s++)
  {
    if (!IsPrint (*s))
      *s = '?';
  }
}