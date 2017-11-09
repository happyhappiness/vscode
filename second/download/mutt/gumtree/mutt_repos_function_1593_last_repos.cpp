static char *maildir_canon_filename (char *dest, const char *src, size_t l)
{
  char *t, *u;

  if ((t = strrchr (src, '/')))
    src = t + 1;

  strfcpy (dest, src, l);
  if ((u = strrchr (dest, ':')))
    *u = '\0';

  return dest;
}