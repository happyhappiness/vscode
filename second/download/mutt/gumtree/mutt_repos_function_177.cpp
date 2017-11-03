void mutt_sanitize_filename (char *f, short slash)
{
  if (!f) return;

  for (; *f; f++)
  {
    if ((slash && *f == '/') || !strchr (safe_chars, *f))
      *f = '_';
  }
}