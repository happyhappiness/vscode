void mutt_safe_path (char *s, size_t l, ADDRESS *a)
{
  char *p;

  mutt_save_path (s, l, a);
  for (p = s; *p; p++)
    if (*p == '/' || ISSPACE (*p) || !IsPrint ((unsigned char) *p))
      *p = '_';
}